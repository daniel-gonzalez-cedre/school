# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 10

import numpy as np
import matplotlib.pyplot as plt

#GRAPH THE LOSS VS ITERATIONS
def graph(data, one_step_means, two_step_means, filename):
    #x_axis = range(1, 301)
    fig, ax = plt.subplots()
    ax.scatter(data[:,0], data[:,1])
    ax.scatter(one_step_means[:,0], one_step_means[:,1], label='One-Step Cluster Means')
    ax.scatter(two_step_means[:,0], two_step_means[:,1], label='Two-Step Cluster Means', color='red')
    legend = ax.legend(loc='best')
    plt.title('Data set: ' + filename)
    plt.savefig('./report/figures/' + filename + '.eps', format='eps', dpi=1000, bbox_inches='tight')

def main():
    xeasy = np.load('./data_parsed/xeasy.data.npy')
    x1 = np.load('./data_parsed/x1.data.npy')
    x2 = np.load('./data_parsed/x2.data.npy')
    xeasy_mean1 = np.array([[0.02478088, 3.07460079], [3.01650103, -0.17460086]])
    xeasy_mean2 = np.array([[3.01183881, -0.17000872], [0.01862825, 3.08197222]])
    x1_mean1 = np.array([[-0.28366821, 2.16960597], [1.83617659, 0.28263171]])
    x1_mean2 = np.array([[1.08395907, 0.85578155], [-0.6095988, 2.74694693]])
    x2_mean1 = np.array([[0.03484, -0.03989854], [0.17023148, -0.14255449]])
    x2_mean2 = np.array([[0.03588655, -0.03956158], [0.16529115, -0.14018644]])

    graph(xeasy, xeasy_mean1, xeasy_mean2, 'xeasy')
    graph(x1, x1_mean1, x1_mean2, 'x1')
    graph(x2, x2_mean1, x2_mean2, 'x2')

main()
