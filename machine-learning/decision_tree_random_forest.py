from collections import namedtuple, Counter
import numpy as np
from multiprocessing import Pool

def report(y_test, y_hat):
    print(metrics.classification_report(y_test, y_hat))

def gini(S, y):
    ## S holds a set of indices into dataset y 
    d = {}
    for i in S:
        d[y[i]] = d.get(y[i], 0) + 1
    p = {c: d[c]/len(S) for c in d.keys()}
    
    gini = 1 - sum([p_c ** 2 for p_c in p.values()])
    return gini

Split = namedtuple("Split", ["j", "v", "gain"])
Node = namedtuple("Node", ["split", "left", "right", "label"], defaults=[None,None,None,None])

class DecisionTree:
    def __init__(self, criterion, max_depth=None):
        self.criterion = criterion
        self.tree = None
        self.max_depth = max_depth
    
    def fit(self, X, y, verbose=False):
       
    
        def evaluate_split(S, L, R):
            gain = self.criterion(S, y)
            gain -= (self.criterion(L, y) * (len(L) / len(S)))
            gain -= (self.criterion(R, y) * (len(R) / len(S)))
            return gain
        
        def make_split(S):
            splits = {}
            ## TODO: add support for categorical variables
            
            for j in range(X.shape[1]):
                if verbose: print("Evaluating possible splits on variable {}".format(j))
                max_gain = 0
                max_gain_split_value = None
                max_gain_L = None
                max_gain_R = None
                
                split_gains = set()
                
                ## Prepare possible 'meaningful' splits along axis j
                V = np.argsort(X[S,j], -1)
                # NOTE: V is a set of indices in the space of S, not X
                # to map a q in V from S->X, use S[q]
                
                for q in range(0, V.shape[0]-1):
                    X_val_l = X[S[q],j]
                    X_val_r = X[S[q+1],j]
                    midpoint = (X_val_l + X_val_r) / 2
                    split_gains.add(midpoint)
                
                ## Evaluate each split
                for z in split_gains:
                    L = list(filter(lambda v: X[v,j] < z, S))
                    R = list(filter(lambda v: X[v,j] >= z, S))
                    
                    z_gain = evaluate_split(S, L, R)
                    if z_gain > max_gain:
                        max_gain = z_gain
                        max_gain_split_value = z
                        max_gain_L = L
                        max_gain_R = R
                

                splits[Split(j, max_gain_split_value, max_gain)] = max_gain_L, max_gain_R
       
            
            max_split = max(splits.keys(), key=lambda k: k.gain)
            
            L, R = splits[max_split]

            return max_split, L, R
        
        
        def make_tree(S, d=0, threshold=0.0):  
            if verbose: print("Building tree at depth {}".format(d))
            
            split, L, R = make_split(S)

            if self.max_depth is not None and d >= self.max_depth:
                best_label = Counter([y[i] for i in L]).most_common(1)[0][0]
                l_tree = Node(label=best_label)
                
                best_label = Counter([y[i] for i in R]).most_common(1)[0][0]
                r_tree = Node(label=best_label)
                
                return Node(split, l_tree, r_tree)
            
            if self.criterion(L, y) > threshold:
                l_tree = make_tree(L, d+1)
            else:
                l_tree = Node(label=y[L[0]])
                
            if self.criterion(R, y) > threshold:
                r_tree = make_tree(R, d+1)
            else:
                r_tree = Node(label=y[R[0]])
            
            return Node(split, l_tree, r_tree)
        
        S = [i for i in range(X.shape[0])]
        if self.criterion(S, y) > 0:
            self.tree = make_tree(S)
        else:
            self.tree = Node(label=y[S[0]])
            
        return self
          

    def predict(self, X):
        
        def traverse(n, x):
            s = n.split

            if s is None:
                return n.label
           
            if(x[s.j] < s.v):
                return traverse(n.left, x)
            else:
                return traverse(n.right, x)
        
        if(X.ndim == 1):
            return traverse(self.tree, X)
        else:
            return [traverse(self.tree, X[i]) for i in range(X.shape[0])]

        
        
class RandomForest:
    def __init__(self, criterion, num_trees=100, max_depth=None, ratio=(2/3)):
        self.criterion = criterion
        self.max_depth = max_depth
        self.num_trees = num_trees
        self.ratio = ratio
        self.trees = []

    def fit(self, X, y, num_threads=1, verbose=False):
        def get_subset_indices():
            N = X.shape[0]
            q = round(N * self.ratio)
            subset = np.random.choice(N, q, replace=True)
            return subset
            
        pool = Pool(num_threads)
        
        for i in range(self.num_trees):
            self.trees.append(DecisionTree(self.criterion, max_depth=self.max_depth))

        async_results = []
        
        for i in range(self.num_trees):
            training_set = get_subset_indices()
            async_results.append(pool.apply_async(self.trees[i].fit, (X[training_set], y[training_set])))
                                 
        pool.close()
        pool.join()
        self.trees = []
        for res in async_results:
            self.trees.append(res.get())
        
    
    def predict(self, X):
        aggregated_y_hat = []
        N = X.shape[0]
        
        for i in range(N):
            aggregated_y_hat.append({})
    
        for t in range(self.num_trees):
            assert(self.trees[t] is not None)
            y_hat = self.trees[t].predict(X)
            
            for i in range(N):
                aggregated_y_hat[i][y_hat[i]] = aggregated_y_hat[i].get(y_hat[i], 0) + 1
                
        max_votes = []
        for i in range(N):
            max_vote = max(aggregated_y_hat[i], key=aggregated_y_hat[i].get)
            max_votes.append(max_vote)
        
        return max_votes

# Test Load Data

from sklearn import metrics, preprocessing
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_digits
import pandas as pd

# dataset A -> Salmon dataset 

A_raw = pd.read_csv('salmon.csv')

A_y = A_raw["Origin"].to_numpy()
A_X = A_raw.loc[:, "Gender" : "Marine"].to_numpy()
A_X_scaled = preprocessing.scale(A_X)

A_X_train, A_X_test, A_y_train, A_y_test = train_test_split(A_X_scaled, A_y, test_size=0.5, shuffle=True)


# dataset B -> MNIST digit classification data

digits=load_digits()
B_y = digits.target
B_X = preprocessing.scale(digits.data)
B_X_train, B_X_test, B_y_train, B_y_test = train_test_split(B_X, B_y, test_size=0.3)

# Test Decision Tree on Salmon Classification

dtree = DecisionTree(gini, max_depth=None)
dtree.fit(A_X_train, A_y_train)

report(A_y_test, dtree.predict(A_X_test))

# Test Random Forest on Salmon Classification

rf = RandomForest(gini, max_depth=3, ratio=(2/3))
rf.fit(A_X_train, A_y_train)
report(A_y_test, rf.predict(A_X_test))

# Test Decision Tree on MNIST Digits

dtree = DecisionTree(gini, max_depth=None)
dtree.fit(B_X_train, B_y_train)

report(B_y_test, dtree.predict(B_X_test))

# Test Random Forest on MNIST Digits

rf = RandomForest(gini, num_trees=100, max_depth=None, ratio=(2/3))
rf.fit(B_X_train, B_y_train, num_threads=8)
report(B_y_test, rf.predict(B_X_test))