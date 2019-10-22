# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 6

import re
import numpy as np
import matplotlib.pyplot as plt

training_data = ["./data-norm/gisette/gisette-train.data.npy", "./data-norm/dexter/dexter-train.csv.npy", "./data-norm/madelon/madelon-train.data.npy"]
test_data = ["./data-norm/gisette/gisette-valid.data.npy", "./data-norm/dexter/dexter-valid.csv.npy", "./data-norm/madelon/madelon-valid.data.npy"]

training_labels = ["./data-norm/gisette/gisette-train.labels.npy", "./data-norm/dexter/dexter-train.labels.npy", "./data-norm/madelon/madelon-train.labels.npy"]
test_labels = ["./data-norm/gisette/gisette-valid.labels.npy", "./data-norm/dexter/dexter-valid.labels.npy", "./data-norm/madelon/madelon-valid.labels.npy"]

#SHRINKAGE FACTOR
s = 0.001
#ANNEALING PARAMETER
μ = 100
#NUMBER OF ITERATIONS
N_itr = 500
#LEARNING RATES FOR DIFFERENT DATA SETS
η_master = [5, 10, 0.01]
#VARIABLE SELECTION PARAMETER
K = [10, 30, 100, 300]

#LOSS FUNCTION
def lorenz_loss(X, Y, β):
    z = Y * np.dot(X, β)
    loss = np.log(1 + (z - 1)**2)
    loss[z > 1] = 0
    return np.sum(loss)/X.shape[0] + s * (np.linalg.norm(β)**2)

#GRADIENT OF LORENZ LOSS
def gradient(X, Y, β):
    ybx = Y * np.dot(X, β)
    f = (2*(ybx - 1)/(1 + (ybx - 1)**2))
    f[ybx > 1] = 0
    return np.dot(X.T, f * Y)/X.shape[0] + 2*s*β

#VARIABLE ELIMINATION; RETAIN ONLY THE Mi FEATURES WITH THE LARGEST L2 NORM
def feature_selection(β, Mi):
    sorted_features = np.flip(np.sort(β**2, kind="mergesort", axis=None))
    threshold = sorted_features[Mi-1]
    count = len([f for f in sorted_features[Mi:] if f == threshold])

    β[β**2 < threshold] = 0
    for i in range(0, β.shape[0]):
        if β[i]**2 == threshold and count > 0:
            β[i] = 0
            count -= 1
        elif count <= 0:
            break
    return β

#FEATURE SELECTION WITH ANNEALING: GRADIENT DESCENT FOLLOWED BY VARIABLE ELIMINATION
def fsa(X, Y, validation, η, k):
    N = X.shape[0]
    M = X.shape[1]
    β = np.zeros(M);
    loss = []
    for i in range(1, N_itr+1):
        β = β - η * gradient(X, Y, β)

        #FIND THE NUMBER OF FEATURES TO RETAIN
        Mi = int(k + (M - k)*max(0, (N_itr - 2*i)/(2*i*μ + N_itr)))
        β = feature_selection(β, Mi)
        indices = np.where(β == 0)

        #DELETE THE IRRELEVANT FEATURES FROM THE WEIGHTS AND DATA
        β = np.delete(β, indices)
        X = np.delete(X, indices, axis=1)
        validation = np.delete(validation, indices, axis=1)
        loss.append(lorenz_loss(X, Y, β))
    return β, X, validation, loss

#PREDICTION
def predict(X, Y, β):
    p = 1/(1 + np.exp(-np.dot(X, β)))
    p[p >= 0.5] = 1
    p[p < 0.5] = -1
    error = np.count_nonzero(Y - p)/Y.shape[0] * 100
    return error

#MAIN PROGRAM
f = open("report/results/results.txt", 'w')

losses = []
for η, f_train_data, f_test_data, f_train_labels, f_test_labels in zip(η_master, training_data, test_data, training_labels, test_labels):
    print("Processing: " + f_train_data.split("/")[-2], file=f)
    for k in K:
        print("\tk = " + str(k), file=f)
        Xtrain = np.load(f_train_data)
        Ytrain = np.load(f_train_labels)
        Xtest = np.load(f_test_data)
        Ytest = np.load(f_test_labels)

        #TRAINING THE MODEL
        β, Xtrain, Xtest, loss = fsa(Xtrain, Ytrain, Xtest, η, k)
        if k == 10:
            losses.append(loss)

        #PREDICT NEW LABELS AND COMPUTE THE MISCLASSIFICATION ERROR
        error_train = predict(Xtrain, Ytrain, β)
        print("\t\tTraining error: " + str(error_train), file=f)
        error_test = predict(Xtest, Ytest, β)
        print("\t\tValidation error: " + str(error_test), file=f)

x_axis = range(1, 501)
fig, ax = plt.subplots()

ax.plot(x_axis, losses[0], label="Gisette")
ax.plot(x_axis, losses[1], label="Dexter")
ax.plot(x_axis, losses[2], label="Madelon")

legend = ax.legend(loc='best')
plt.title(r'Training Loss vs. Iterations')
plt.xticks([1, 100, 200, 300, 400, 500], [1, 100, 200, 300, 400, 500])
plt.xlabel("Iteration Number")
plt.ylabel("Training Loss")
plt.savefig("./report/figures/graph.eps", format="eps", dpi=1000, bbox_inches="tight")
