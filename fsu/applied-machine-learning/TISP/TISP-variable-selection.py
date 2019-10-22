# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 4

import re
import numpy as np
import matplotlib.pyplot as plt

training_data = ["./data-norm/gisette/gisette_train.data.npy", "./data-norm/dexter/dexter_train.csv.npy", "./data-norm/madelon/madelon_train.data.npy"]
test_data = ["./data-norm/gisette/gisette_valid.data.npy", "./data-norm/dexter/dexter_valid.csv.npy", "./data-norm/madelon/madelon_valid.data.npy"]

training_labels = ["./data-norm/gisette/gisette_train.labels.npy", "./data-norm/dexter/dexter_train.labels.npy", "./data-norm/madelon/madelon_train.labels.npy"]
test_labels = ["./data-norm/gisette/gisette_valid.labels.npy", "./data-norm/dexter/dexter_valid.labels.npy", "./data-norm/madelon/madelon_valid.labels.npy"]

λ_master = [[0.197, 0.135, 0.08745, 0.053], [0.15, 0.0983663, 0.0713, 0.05269], [0.029799, 0.02435, 0.01695, 0.0074]]

#GRADIENT DESCENT FOLLOWED BY THRESHOLD
def theta(X, Y, η=1, λ=0, itr=100):
    w = np.zeros((X.shape[1]+1, 1))
    X = np.asarray([np.append(1, x) for x in X])
    for i in range(0, itr):
        w = w + η * np.dot(X.T, Y - 1/(1 + np.exp(-np.dot(X, w))))
        mask = np.ones(w.shape, bool)
        mask[0] = False
        w[(np.abs(w) <= λ) & (mask)] = 0
    return w

#PREDICTING LABELS
def predict(w, X):
    X = np.asarray([np.append(1, x) for x in X])
    prediction = np.dot(X, w)
    prediction[prediction > 0] = 1
    prediction[prediction <= 0] = 0
    return prediction

#MAIN DATA PROCESSING
for λ_list, f_train_data, f_test_data, f_train_labels, f_test_labels in zip(λ_master, training_data, test_data, training_labels, test_labels):
    print("Processing: " + f_train_data.split("/")[-2])
    Xtrain = np.load(f_train_data)
    Ytrain = np.load(f_train_labels)
    Xtest = np.load(f_test_data)
    Ytest = np.load(f_test_labels)
    η = 1/Xtrain.shape[0]
    train_error = []
    test_error = []

    #ITERATE OVER NUMBER OF FEATURES SELECTED
    for λ in λ_list:
        w = theta(Xtrain, Ytrain, η, λ)
        print("\t λ = " + str(λ))
        print("\t Features: " + str(np.count_nonzero(w) - 1))
        train_prediction = predict(w, Xtrain)
        test_prediction = predict(w, Xtest)

        train_error.append(100*np.count_nonzero(Ytrain - train_prediction)/Ytrain.shape[0])
        test_error.append(100*np.count_nonzero(Ytest - test_prediction)/Ytest.shape[0])
        print("\t\t" + "training error: " + str(train_error[-1]) + "%")
        print("\t\t" + "validation error: " + str(test_error[-1]) + "%")

    #GRAPHING
    num_features = [10, 30, 100, 300]
    fig, ax = plt.subplots()
    ax.plot(num_features, train_error, label="Training Error")
    ax.plot(num_features, test_error, label="Test Error")
    legend = ax.legend(loc='best')
    plt.title(f_train_data.split("/")[-2])
    plt.xticks(num_features, num_features)
    plt.xlabel("Number of Features Selected")
    plt.ylabel("Misclassification Error %")
    plt.savefig("./report/figures/" + f_train_data.split("/")[-2] + ".eps", format="eps", dpi=1000, bbox_inches="tight")
