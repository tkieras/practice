from sklearn import metrics, preprocessing
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_digits, make_circles, load_iris

import matplotlib.pyplot as plt
import numpy as np

from cvxopt import matrix, solvers
from collections import namedtuple
from itertools import combinations

def report(y_test, y_hat):
    print("Classification Report")
    print(metrics.classification_report(y_test, y_hat))

def make_poly_kernel(d):
    def poly_kernel(x1,x2):
        return (np.dot(x1,x2)+1)**d
    return poly_kernel

def kernel_lin(x1,x2):
    return np.dot(x1,x2)


class Svm:
    def __init__(self, kernel, y=None):
        self.kernel = kernel
        self.svm_alphas = None
        self.intercept = None
        self.map_class_y = self.prepare_map_class_y(y)
        self.map_y_class = self.prepare_map_y_class()
    
    def prepare_map_class_y(self, y):
        # Utility function to initialize y label mapping
        if y is None:
            return None
        map_class_y = {}

        for i in range(y.shape[0]):
            map_class_y[y[i]] = 0
        
        if len(map_class_y.keys()) != 2:
            raise ValueError("Svm basic class requires exactly two classes")
        
        first = list(map_class_y.keys())[0]
        second = list(map_class_y.keys())[1]
        
        map_class_y[first] = 1.0
        map_class_y[second] = -1.0
        
        return map_class_y
    
    def prepare_map_y_class(self):
        if self.map_class_y is None:
            return None
        else:
            map_y_class = {value : key for key, value in self.map_class_y.items()}
            return map_y_class

        
    def fit(self, X, y, C=None):
        ## Make sure y is properly setup for SVM
        if self.map_class_y is not None:
            y = np.array(list(map(lambda c: self.map_class_y[c], y)))

        y = y[:,np.newaxis]

        m = len(X)
        P = np.zeros((m,m))
        
        for i in range(m):
            for j in range(m):
                P[i,j] = y[i] * y[j] * self.kernel(X[i], X[j])

        P = matrix(P)

        q = matrix(-1 * np.ones((m,1)))
        G = matrix(-1 * np.eye(m))
        h = matrix(np.zeros((m,1)))

        if C is not None:
            G = matrix(np.vstack((G, np.eye(m))))
            h = matrix(np.hstack((np.zeros(m), np.ones(m) * C)))

        A = matrix(y.T)
        b = matrix(0.0)
        
        solvers.options["show_progress"] = False
        sol = solvers.qp(P, q, G, h, A, b)
        
        if(sol["status"] != "optimal"):
            raise RuntimeError("Solver exited with status: {}".format(sol["status"]))
        
        alphas = sol["x"]
        
        alphas = np.array(list(map(lambda a: a if a > (1/1000) else 0, [a for a in alphas])))
        
        try:
            k = np.nonzero(alphas)[0][0]
        except IndexError:
            raise RuntimeError("Unable to find support vectors.")

        b = y[k] - sum([alphas[i] * y[i] * self.kernel(X[i], X[k]) for i in range(m)])

        self.svm_alphas = alphas
        self.intercept = b.item()
        self.fit_X = X
        self.fit_y = y    
    
    def predict(self, X):
        def predict_single(x):
            result = sum([(self.svm_alphas[i] * self.fit_y[i] * self.kernel(self.fit_X[i], x)) 
                          for i in range(self.fit_X.shape[0])])
            result += self.intercept    
            return np.sign(result)[0]
        
        results = []

        if(X.ndim == 1):
            results.append(predict_single(X))
        else:
            num_items = X.shape[0]

            for z in range(num_items):
                results.append(predict_single(X[z]))

        if self.map_y_class is not None:
            return list(map(lambda y: self.map_y_class[y], results))
        else:
            return results


class SvmMulticlass:
    def __init__(self, kernel, y):
        self.kernel = kernel
        self.classes = set()
        self.svm_set = []
        self.scalers = []

        for i in range(y.shape[0]):
            self.classes.add(y[i])
            
    def fit(self, X, y, C=None, verbose=False):
        def extract_subset(pair):
            subset = []
            for i in range(len(y)):
                if y[i] in pair:
                    subset.append(i)
            return subset
        
        # Use One-to-One Approach
        ## Each classifier should be good at distinguishing class 'A' from class 'B'
        ### For all combinations A, B in possible labels
        all_pairs = list(combinations(self.classes, 2))

        for i in range(len(all_pairs)):
            if verbose: print("Training classifier {}/{} for class pair {}".format(i+1, len(all_pairs), all_pairs[i]))
            
            subset = extract_subset(all_pairs[i])
            svm = Svm(self.kernel, y[subset])
            scaler = preprocessing.Normalizer()
            new_x = scaler.fit_transform(X[subset])
            self.scalers.append(scaler)
            svm.fit(new_x, y[subset], C)
            self.svm_set.append(svm)
        
    def predict(self, X, verbose=False):
        aggregated_y_hat = []
        N = X.shape[0]
        
        for i in range(N):
            aggregated_y_hat.append({})
    
        for t in range(len(self.svm_set)):
            if verbose: print("Predicting with classifier {}/{}".format(t+1, len(self.svm_set)))
            
            new_X = self.scalers[t].transform(X)
            y_hat = self.svm_set[t].predict(new_X)
            
            for i in range(N):
                aggregated_y_hat[i][y_hat[i]] = aggregated_y_hat[i].get(y_hat[i], 0) + 1
                
        max_votes = []
        for i in range(N):
            max_vote = max(aggregated_y_hat[i], key=aggregated_y_hat[i].get)
            max_votes.append(max_vote)
        
        return max_votes

# Load Iris Dataset

A_X, A_y = load_iris(return_X_y=True)
A_X_train, A_X_test, A_y_train, A_y_test = train_test_split(A_X, A_y, test_size=0.3, shuffle=True)

# SVM Multiclass, Linear Kernel, Soft-Margin

mysvm = SvmMulticlass(kernel_lin, A_y_train)

mysvm.fit(A_X_train, A_y_train, C=1)
y_hat = mysvm.predict(A_X_test)

print(metrics.classification_report(A_y_test, y_hat))

# SVM Multiclass, Linear Kernel, Soft-Margin

mysvm = SvmMulticlass(make_poly_kernel(3), A_y_train)

mysvm.fit(A_X_train, A_y_train, C=1)
y_hat = mysvm.predict(A_X_test)

print(metrics.classification_report(A_y_test, y_hat))

# Load MNIST Digits

digits=load_digits()
B_y = digits.target
B_X = preprocessing.scale(digits.data)

B_X_train, B_X_test, B_y_train, B_y_test = train_test_split(B_X, B_y, test_size=0.3)

# SVM Multiclass, Linear Kernel, Soft Margin

multisvm = SvmMulticlass(kernel_lin, B_y_train)
multisvm.fit(B_X_train, B_y_train, C=1, verbose=False)
y_hat = multisvm.predict(B_X_test)

print(metrics.classification_report(B_y_test, y_hat))

# SVM Multiclass, Polynomial (3) Kernel, Soft-Margin

multisvm = SvmMulticlass(make_poly_kernel(3), B_y_train)
multisvm.fit(B_X_train, B_y_train, C=1, verbose=False)
y_hat = multisvm.predict(B_X_test, verbose=False)

print(metrics.classification_report(B_y_test, y_hat))

# Load Circles

C_X, C_y = make_circles(n_samples=5000, shuffle=True, noise=0.1, factor=.1)
C_X_train, C_X_test, C_y_train, C_y_test = train_test_split(C_X, C_y, test_size=0.5, shuffle=True)

def plot_data(X, y):
    class_1 = np.where(y == 1)
    class_0 = np.where(y == 0)

    plt.figure(figsize=(14,8))
    plt.scatter(X[class_1,0], X[class_1,1], c='b', marker="o")
    plt.scatter(X[class_0,0], X[class_0,1], c='g', marker="x")
    plt.xlabel('x1')
    plt.ylabel('x2');
   # plt.savefig("circles.png", dpi=300)
    plt.grid()

plot_data(C_X_train, C_y_train)

# Circles, SVM Polynomial (2)

mysvm = Svm(make_poly_kernel(2), C_y_train)

mysvm.fit(C_X_train, C_y_train, C=.5)
y_hat = mysvm.predict(C_X_test)

print(metrics.classification_report(C_y_test, y_hat))