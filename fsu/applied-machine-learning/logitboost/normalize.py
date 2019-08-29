# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 8

import re
import numpy as np

training_data = ["./data/gisette/gisette_train.data", "./data/dexter/dexter_train.csv", "./data/madelon/madelon_train.data"]
test_data = ["./data/gisette/gisette_valid.data", "./data/dexter/dexter_valid.csv", "./data/madelon/madelon_valid.data"]

training_labels = ["./data/gisette/gisette_train.labels", "./data/dexter/dexter_train.labels", "./data/madelon/madelon_train.labels"]
test_labels = ["./data/gisette/gisette_valid.labels", "./data/dexter/dexter_valid.labels", "./data/madelon/madelon_valid.labels"]

#MAIN DATA PROCESSING
for f_train_data, f_test_data, f_train_labels, f_test_labels in zip(training_data, test_data, training_labels, test_labels):
    with open(f_train_data) as train, open(f_test_data) as test, open(f_train_labels) as train_labels, open(f_test_labels) as test_labels:
        print("Processing: " + str(f_train_data.split("/")[-1]))
        data = []
        valid = []
        data_labels = []
        valid_labels = []

        #INPUT DATA
        for line in train:
            data.append([float(x) for x in re.split(r'[, ]', line.strip().strip("\n"))])
        for line in test:
            valid.append([float(x) for x in re.split(r'[, ]', line.strip().strip("\n"))])
        for line in train_labels:
            data_labels.append([float(x) for x in re.split(r'[ ]', line.strip().strip("\n"))])
        for line in test_labels:
            valid_labels.append([float(x) for x in re.split(r'[ ]', line.strip().strip("\n"))])

        #AUGMENT THE DATA MATRICES WITH A COLUMN OF 1 ON THE LEFT
        data = np.insert(np.asarray(data), 0, 1, axis=1)
        valid = np.insert(np.asarray(valid), 0, 1, axis=1)
        data_labels = np.asarray(data_labels)
        valid_labels = np.asarray(valid_labels)

        data_labels = data_labels.reshape(data_labels.shape[0])
        valid_labels = valid_labels.reshape(valid_labels.shape[0])

        #RELABEL
        data_labels[data_labels != 1] = -1
        valid_labels[valid_labels != 1] = -1

        #OUTPUT DATA
        print("\t Writing normalized training data...")
        np.save("./data_norm/" + f_train_data.split("/")[-2] + "/" + f_train_data.split("/")[-1], data)

        print("\t Writing normalized validation data...")
        np.save("./data_norm/" + f_test_data.split("/")[-2] + "/" + f_test_data.split("/")[-1], valid)

        print("\t Writing training labels...")
        np.save("./data_norm/" + f_train_labels.split("/")[-2] + "/" + f_train_labels.split("/")[-1], data_labels)

        print("\t Writing validation labels...")
        np.save("./data_norm/" + f_test_labels.split("/")[-2] + "/" + f_test_labels.split("/")[-1], valid_labels)
