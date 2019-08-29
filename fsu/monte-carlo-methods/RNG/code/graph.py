import re
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

def graph_randu(X, Y, filename):
    fig, ax = plt.subplots()
    ax.scatter(X[0], Y[0], marker='.', label='seed: 3')
    ax.scatter(X[1], Y[1], marker='.', label='seed: 5')
    ax.scatter(X[2], Y[2], marker='.', label='seed: 7')
    ax.scatter(X[3], Y[3], marker='.', label='seed: 9')
    ax.scatter(X[4], Y[4], marker='.', label='seed: 101')
    legend = ax.legend(loc='upper right')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_mersenne(X, Y, filename):
    fig, ax = plt.subplots()
    ax.scatter(X, Y, marker='.')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_halton(X1, Y1, X2, Y2, filename):
    fig, ax = plt.subplots()
    ax.scatter(X2, Y2, marker='$\cdot$', label='mersenne')
    ax.scatter(X1, Y1, marker='.', label='2D halton')
    plt.xlabel('base 2')
    plt.ylabel('base 3')
    legend = ax.legend(loc='upper right')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_quadrature(Y1, Y2, filename):
    fig, ax = plt.subplots()
    ax.plot(Y1, label='MC')
    ax.plot(Y2, label='RQMC')
    ax.plot([np.exp(1)-1 for i in range(1, 41)], label=r'$\int e^x dx$')
    plt.xlabel('$k$')
    plt.ylabel(r'$\theta_k$')
    legend = ax.legend(loc='upper right')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def main():
    randuX = [\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[0]) for line in open('../output/randu3.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[0]) for line in open('../output/randu5.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[0]) for line in open('../output/randu7.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[0]) for line in open('../output/randu9.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[0]) for line in open('../output/randu101.dat')]]
    randuY = [\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[1]) for line in open('../output/randu3.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[1]) for line in open('../output/randu5.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[1]) for line in open('../output/randu7.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[1]) for line in open('../output/randu9.dat')],\
            [float(line.strip().strip('\n').strip('(').strip(')').split(',')[1]) for line in open('../output/randu101.dat')]]

    mersenneX1 = [float(line.strip().strip('\n').strip('[').strip(']').split(',')[0]) for line in open('../output/mersenne_pairs.dat')]
    mersenneY1 = [float(line.strip().strip('\n').strip('[').strip(']').split(',')[1]) for line in open('../output/mersenne_pairs.dat')]

    haltonX = [float(line.strip().strip('\n').strip('[').strip(']').split(',')[0]) for line in open('../output/halton.dat')]
    haltonY = [float(line.strip().strip('\n').strip('[').strip(']').split(',')[1]) for line in open('../output/halton.dat')]
    mersenneX2 = [float(line.strip().strip('\n').strip('[').strip(']').split(',')[0]) for line in open('../output/mersenne.dat')]
    mersenneY2 = [float(line.strip().strip('\n').strip('[').strip(']').split(',')[1]) for line in open('../output/mersenne.dat')]

    MC1 = [float(x) for x in [line.strip().strip('\n').strip('[').strip(']').split(',') for line in open('../output/MC1.dat')][0]]
    MC2 = [float(x) for x in [line.strip().strip('\n').strip('[').strip(']').split(',') for line in open('../output/MC2.dat')][0]]
    RQMC1 = [float(x) for x in [line.strip().strip('\n').strip('[').strip(']').split(',') for line in open('../output/RQMC1.dat')][0]]
    RQMC2 = [float(x) for x in [line.strip().strip('\n').strip('[').strip(']').split(',') for line in open('../output/RQMC2.dat')][0]]

    graph_randu(randuX, randuY, 'randu')
    graph_mersenne(mersenneX1, mersenneY1, 'mersenne2D')
    graph_halton(haltonX, haltonY, mersenneX2, mersenneY2, 'halton')
    graph_quadrature(MC1, RQMC1, 'MC1')
    graph_quadrature(MC2, RQMC2, 'MC2')

main()
