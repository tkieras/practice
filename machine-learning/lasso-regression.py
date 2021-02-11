from sklearn import metrics, datasets, preprocessing
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import numpy as np

# dataset A -> From class
# Here, Boston Housing dataset 

poly = preprocessing.PolynomialFeatures(degree=4, include_bias=False)

A_raw = datasets.load_boston()
A_y = A_raw.target
A_X = A_raw.data
A_X_scaled = preprocessing.scale(A_X)

A_X_trnsf = poly.fit_transform(A_X_scaled)

A_X_train, A_X_test, A_y_train, A_y_test = train_test_split(A_X_trnsf, A_y, test_size=0.5, shuffle=True)


# dataset B -> Not from in class
# https://archive.ics.uci.edu/ml/datasets/Auto+MPG

with open("auto-mpg.data", "r") as infile:
    lines = infile.readlines()

B_y = []
B_X = []

for line in lines:
    line = line.split("\t")
    nums = line[0].split()
    x = []
    try:
        x = [float(nums[i]) for i in range(1,8)]
        B_y.append(float(nums[0]))
        B_X.append(x)
    except ValueError:
        pass
B_y = np.array(B_y)
B_X = np.array(B_X)

poly = preprocessing.PolynomialFeatures(degree=4, include_bias=False)

B_X_scaled = preprocessing.scale(B_X)
B_X_scaled = poly.fit_transform(B_X_scaled)
B_X_train, B_X_test, B_y_train, B_y_test = train_test_split(B_X_scaled, B_y, test_size=0.5, shuffle=True)

def report(y_test, y_hat):
    print("Mean Squared Error: {}".format(mse(y_test, y_hat)))

def mse(y, y_hat):
    err = sum([(y[i] - y_hat[i])**2 for i in range(len(y))]) / len(y)   
    return err.item()


def soft_threshold(rho_j, lambd):
    if rho_j < -lambd:
        return rho_j + lambd
    elif rho_j > lambd:
        return rho_j - lambd
    else:
        return 0
    
class Lasso:
    def __init__(self):
        self.w = None
        self.w_history = []
        self.lambd = None
    
    def fit(self, X, y, lambd, num_iter=100, fit_intercept=False, tol=1e-6, verbose=False):
        mse_history = []
        
        X = preprocessing.normalize(X, axis=0)

        y = y[:,None]

        N = X.shape[1]

        w = np.ones((N,1))

        for c in range(num_iter):
            if c % 10 == 0:
                if verbose: print("Iteration {}/{}".format(c, num_iter))
                tmp = np.matmul(X,w)
                err = mse(tmp, y)
                mse_history.append(err)
                self.w_history.append(np.copy(w))
                
                if len(mse_history) > 2:
                    prev = mse_history[len(mse_history)-2]
                    if (np.abs(err - prev)) < (tol * prev):
                        if verbose: print("Stopping at {}/{} iterations because tolerance was reached".format(c, num_iter))
                        break
                          
            for j in range(N):
                k_not_j = [k for k in range(N) if k != j]

                res = y - np.matmul(X[:, k_not_j], w[k_not_j])

                rho_j = np.matmul(X[:,j].reshape(-1,1).T, res)

                ## Add the appropriate subdifferential of the l1 function
                update = soft_threshold(rho_j, lambd)

                if(j==0 and fit_intercept):
                    update = rho_j

                w[j] = update
        
        self.w = w
        self.lambd = lambd
        
    def plot_history(self, X_train, X_test, y_train, y_test, name):
        X_train = preprocessing.normalize(X_train, axis=0)
        X_test = preprocessing.normalize(X_test, axis=0)
        train_err = []
        test_err = []
        x_vals = range(len(self.w_history))
        
        for i in x_vals:
            y_hat_train = X_train @ self.w_history[i]
            y_hat_test = X_test @ self.w_history[i]
            train_err.append(mse(y_hat_train, y_train))
            test_err.append(mse(y_hat_test, y_test))
        
        
        plt.plot(x_vals, train_err, marker=".", linestyle="-", c="red", label="Training Error")
        plt.plot(x_vals, test_err, marker=".", linestyle="-", c="green", label="Test Error")
        
        plt.title('Coordinate Descent Iteration vs MSE, lambda={}'.format(self.lambd))
        plt.xlabel('Iteration (x10)')
        plt.ylabel('Mean Squared Error')
        plt.legend()
        plt.grid()
        plt.savefig(name, dpi=300)
        plt.show()
        
    
    def predict(self, X):
        X = preprocessing.normalize(X, axis=0)
        return np.matmul(X, self.w)
    

# Basic algorithm for Dataset A

model = Lasso()
model.fit(A_X_train, A_y_train, 0, verbose=True)

print("Training Error:")
report(A_y_train, model.predict(A_X_train))

print("Testing Error:")
report(A_y_test, model.predict(A_X_test))

model.plot_history(A_X_train, A_X_test, A_y_train, A_y_test, "basic_a.png")

# Lasso on Dataset A

model = Lasso()
model.fit(A_X_train, A_y_train, 1, verbose=True)

print("Training Error:")
report(A_y_train, model.predict(A_X_train))

print("Testing Error:")
report(A_y_test, model.predict(A_X_test))

model.plot_history(A_X_train, A_X_test, A_y_train, A_y_test, "ext_a.png")

# Basic algorithm on Dataset B

model = Lasso()
model.fit(B_X_train, B_y_train, 0, num_iter=1000, verbose=True)

print("Training Error:")
report(B_y_train, model.predict(B_X_train))

print("Testing Error:")
report(B_y_test, model.predict(B_X_test))

model.plot_history(B_X_train, B_X_test, B_y_train, B_y_test, "basic_b.png")

# Lasso on Dataset B

model = Lasso()
model.fit(B_X_train, B_y_train, 1, num_iter=1000, verbose=True)

print("Training Error:")
report(B_y_train, model.predict(B_X_train))

print("Testing Error:")
report(B_y_test, model.predict(B_X_test))

model.plot_history(B_X_train, B_X_test, B_y_train, B_y_test, "ext_b.png")