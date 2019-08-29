# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 3

from math import sqrt

training_data = ["./data/gisette/gisette_train.data", "./data/madelon/madelon_train.data", "./data/hill-valley/X.dat"]
test_data = ["./data/gisette/gisette_valid.data", "./data/madelon/madelon_valid.data", "./data/hill-valley/Xtest.dat"]

training_labels = ["./data/gisette/gisette_train.labels", "./data/madelon/madelon_train.labels", "./data/hill-valley/Y.dat"]
test_labels = ["./data/gisette/gisette_valid.labels", "./data/madelon/madelon_valid.labels", "./data/hill-valley/Ytest.dat"]

for f_train_data, f_test_data, f_train_labels, f_test_labels in zip(training_data, test_data, training_labels, test_labels):
    with open(f_train_data) as train, open(f_test_data) as test, open(f_train_labels) as train_labels, open(f_test_labels) as test_labels:
        print("Processing: " + str(f_train_data.split("/")[-1]))
        N = 0
        flag = True
        for line in train:
            N = N + 1
            line = [float(x) for x in line.strip().strip("\n").split(" ")]
            if(flag):
                avg = line
                flag = False
            else:
                avg = [x + y for x, y in zip(avg, line)]
        avg = [x/N for x in avg]

        train.seek(0)
        flag = True

        for line in train:
            line = [float(x) for x in line.strip().strip("\n").split(" ")]
            if(flag):
                shifted = [[x - y for x, y in zip(line, avg)]]
                std = [x**2 for x in shifted[-1]]
                flag = False
            else:
                shifted.append([x - y for x, y in zip(line, avg)])
                std = [x + y**2 for x, y in zip(std, shifted[-1])]
        std = [sqrt(x) for x in std]
        norm = [[x/s for x, s in zip(vector, std) if s != 0] for vector in shifted]

        with open("./data_norm/" + f_train_data.split("/")[-2] + "/" + f_train_data.split("/")[-1], "w") as output:
            for vector in norm:
                for x in vector:
                    output.write(str(x) + " ")
                output.write("\n")

        print("Processing: " + str(f_test_data.split("/")[-1]))
        norm = []
        for line in test:
            line = [float(x) for x in line.strip().strip("\n").split(" ")]
            norm.append([(x - m)/s for x, m, s in zip(line, avg, std) if s != 0])

        with open("./data_norm/" + f_test_data.split("/")[-2] + "/" + f_test_data.split("/")[-1], "w") as output:
            for vector in norm:
                for x in vector:
                    output.write(str(x) + " ")
                output.write("\n")

        print("Processing: " + str(f_train_labels).split("/")[-1])
        with open("./data_norm/" + f_train_labels.split("/")[-2] + "/" + f_train_labels.split("/")[-1], "w") as output:
            for line in train_labels:
                line = [int(x) for x in line.strip().strip("\n").split(" ")]
                if line[0] == 1:
                    output.write("1\n")
                else:
                    output.write("0\n")

        print("Processing: " + str(f_test_labels).split("/")[-1])
        with open("./data_norm/" + f_test_labels.split("/")[-2] + "/" + f_test_labels.split("/")[-1], "w") as output:
            for line in test_labels:
                line = [int(x) for x in line.strip().strip("\n").split(" ")]
                if line[0] == 1:
                    output.write("1\n")
                else:
                    output.write("0\n")
