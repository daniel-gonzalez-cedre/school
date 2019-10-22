# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 3

from math import exp
from math import log
import numpy as np
import matplotlib.pyplot as plt

training_data = ["./data-norm/madelon/madelon_train.data"]
test_data = ["./data-norm/madelon/madelon_valid.data"]

training_labels = ["./data-norm/madelon/madelon_train.labels"]
test_labels = ["./data-norm/madelon/madelon_valid.labels"]

def gradient(X, Y, weights):
    N = X.shape[0]
    M = X[0].shape[0]

    grad = np.zeros(M+1)
    x = np.asarray([np.append([1], x) for x in X])
    xT = np.transpose(x)
    W = weights.reshape(1, M+1)
    fraction = np.exp(np.inner(W, x)).transpose()
    fraction = (fraction / (1 + fraction))
    grad = np.dot(xT, Y - fraction)

    return grad 

def gradient_ascent(X, Y, η=1, λ=0.001, num_itr=10000):
    llh = np.array([])
    N = X.shape[0]
    M = X[0].shape[0]
    weights = np.zeros(M + 1)

    for itr in range(0, num_itr+1):
        print(itr)
        grad = gradient(X, Y, weights)[:,0]
        weights = ((1 - η * λ) * weights) + ((η / N) * grad)
        print(weights.shape)
        if itr % 25 == 0:
            llh = np.append(llh, log_likelihood(X, Y, weights))

    return (weights, llh)

def log_likelihood(X, Y, weights):
    llh = 0
    N = X.shape[0]
    M = X[0].shape[0]

    for j in range(0, N):
        x = np.append([1], X[j])
        product = np.inner(x, weights)
        llh = llh + Y[j, 0] * product - np.log(1 + np.exp(product))

    return np.array(llh)

for f_train_data, f_test_data, f_train_labels, f_test_labels in zip(training_data, test_data, training_labels, test_labels):
    with open(f_train_data) as train_data, open(f_test_data) as test_data, open(f_train_labels) as train_labels, open(f_test_labels) as test_labels:
        output_train_error = open("./output/train-error-" + f_train_data.split("/")[-2], "w")
        output_test_error = open("./output/test-error-" + f_train_data.split("/")[-2], "w")

        train_error = 0
        test_error = 0
        llh = np.array([])
        train_predictions = np.array([])
        test_predictions = np.array([])

        print("Processing: " + f_train_data.split("/")[-1])
        Xtrain = np.asarray([[float(x) for x in line.strip().strip("\n").split(" ")] for line in train_data])
        Ytrain = np.asarray([[float(x) for x in line.strip().strip("\n").split(" ")] for line in train_labels])
        Xtest = np.asarray([[float(x) for x in line.strip().strip("\n").split(" ")] for line in test_data])
        Ytest = np.asarray([[float(x) for x in line.strip().strip("\n").split(" ")] for line in test_labels])

        results = gradient_ascent(Xtrain, Ytrain)
        weights = results[0]
        llh = results[1]

        for x in Xtrain:
            if np.inner(np.append([1], x), weights) > 0:
                train_predictions = np.append(train_predictions, [1])
            else:
                train_predictions = np.append(train_predictions, [0])

        for x in Xtest:
            if np.inner(np.append([1], x), weights) > 0:
                test_predictions = np.append(test_predictions, [1])
            else:
                test_predictions = np.append(test_predictions, [0])

        for y, p in zip(Ytrain, train_predictions):
            if y != p:
                train_error = train_error + 1

        for y, p in zip(Ytest, test_predictions):
            if y != p:
                test_error = test_error + 1

        print(llh)

        output_train_error.write(str(train_error/(Ytrain.shape[0])) + "\n")
        output_test_error.write(str(test_error/(Ytest.shape[0])) + "\n")

        axes = [x for x in range(0, 10001) if (x % 25 == 0)]
        fig, ax = plt.subplots()
        ax.plot(axes, llh)
        plt.title("Madelon")
        plt.xticks([x for x in range(0, 10001) if (x%1000 == 0)], [x for x in range(0, 10001) if (x%1000 == 0)])
        plt.xlabel("Iteration Counter")
        plt.ylabel("Log-Likelihood")
        plt.savefig("./report/figures/madelon.eps", format="eps", dpi=1000, bbox_inches="tight")
