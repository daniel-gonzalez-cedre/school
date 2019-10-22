# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 10

from __future__ import print_function
import random
import numpy as np
import matplotlib.pyplot as plt
from sklearn.mixture import GaussianMixture

#PARAMETERS FOR THE SCIKITLEARN GAUSSIAN MIXTURE MODEL
#---N_COMPONENTS:------NUMBER OF CLUSTERS                                                   | DEFAULT: 1
#---COVARIANCE_TYPE:---'full' MEANS EVERY CLUSTER HAS ITS OWN INDEPENDENT COVARIANCE MATRIX | DEFAULT: 'full'
#---TOL:---------------TOLERANCE FOR CONVERGENCE                                            | DEFAULT: 1e-3
#---MAX_ITER:----------EM ALGORITHM WILL RUN FOR max_itr ITERATIONS UNTIL CONVERGENCE       | DEFAULT: 100
#---N_INIT:------------NUMBER OF INITIALIZATIONS TO PERFORM, KEEPING ONLY THE BEST RESULTS  | DEFAULT: 1
#---INIT_PARAMS:-------HOW TO INITIALIZE THE WEIGHTS, MEANS, AND VARIANCES                  | DEFAULT: 'kmeans'
#---WEIGHTS_INIT:------USER PROVIDES WEIGHTS FOR EACH CLUSTER MANUALLY                      | DEFAULT: init_params method
#---MEANS_INIT:--------USER PROVIDES MEANS FOR EACH CLUSTER MANUALLY                        | DEFAULT: init_params method
#---PRECISIONS_INIT:---USER PROVIDES INVERSES FOR THE COVARIANCE MATRICES MANUALLY          | DEFAULT: init_params method

#PROVABLE (TWO-STEP) EM ALGORITHM
def provable_EM(data, k, l):
    #INITIALIZING PARAMETERS
    weights = [1./l, 1./l, 1./l, 1./l]
    means = data[np.random.choice(data.shape[0], l)]
    sigma = []
    cov = []
    for i in range(0, l):
        sigma.append(np.amin([np.linalg.norm(means[i] - x) for x in np.reshape(means[means != means[i]], (l-1, 2))]))
    for i in range(0, l):
        cov.append(np.identity(2)*(1./sigma[i]))

    #FIRST PASS OF EM ALGORITHM
    GM = GaussianMixture(n_components=l, n_init=5, weights_init=weights, means_init=means, precisions_init=cov).fit(data)
    weights = GM.weights_
    means = GM.means_
    prec = GM.precisions_

    #PRUNING
    pruned = [i for i in range(0, l) if weights[i] < 1./(4*l)]
    weights = np.delete(weights, pruned, 0)
    means = np.delete(means, pruned, 0)
    prec = np.delete(prec, pruned, 0)

    #COMPUTE THE NEW INITIAL VALUES
    S_weights = np.array([weights[0]])
    S_means = np.array([means[0]])
    S_prec = np.array([prec[0]])
    means = means = np.delete(means, 0, 0)
    while S_means.shape[0] < k:
        d = 0
        for mu in means:
            mu_dist = np.amin([np.linalg.norm(mu - s) for s in S_means])
            if mu_dist > d:
                d = mu_dist
                curr = mu
        index = np.where(means==mu)[0][0]
        S_weights = np.append(S_weights, [weights[index]], axis=0)
        S_means = np.append(S_means, [means[index]], axis=0)
        S_prec = np.append(S_prec, [prec[index]], axis=0)
        means = np.delete(means, index, 0)

    #NORMALIZE THE WEIGHTS
    S_weights = S_weights/np.sum(S_weights)

    #SECOND PASS OF EM ALGORITHM
    return GaussianMixture(n_components=k, n_init=5, weights_init=S_weights, means_init=S_means, precisions_init=S_prec).fit(data)

#MAIN BLOCK
def main():
    with open('./output/results.txt', 'w') as f:
        xeasy = np.load('./data-parsed/xeasy.data.npy')
        x1 = np.load('./data-parsed/x1.data.npy')
        x2 = np.load('./data-parsed/x2.data.npy')

        #ONE-STEP EM ALGORITHM
        print('ONE-STEP EM:', file=f)
        GMeasy = GaussianMixture(n_components=2, n_init=5).fit(xeasy)
        GM1 = GaussianMixture(n_components=2, n_init=5).fit(x1)
        GM2 = GaussianMixture(n_components=2, n_init=5).fit(x2)
        print_results(GMeasy, GM1, GM2, f)

        print('==========================================', file=f)
        #TWO-STEP EM ALGORITHM
        print('TWO-STEP EM:', file=f)
        GMeasy = provable_EM(xeasy, 2, 4)
        GM1 = provable_EM(x1, 2, 4)
        GM2 = provable_EM(x2, 2, 4)
        print_results(GMeasy, GM1, GM2, f)

def print_results(GMeasy, GM1, GM2, f):
    print('xeasy', file=f)
    print('pi: ', file=f)
    print(GMeasy.weights_, file=f)
    print('mu: ', file=f)
    print(GMeasy.means_, file=f)
    print('sigma: ', file=f)
    print(GMeasy.covariances_, file=f)
    print('------------------------------------------', file=f)
    print('x1', file=f)
    print('pi: ', file=f)
    print(GM1.weights_, file=f)
    print('mu: ', file=f)
    print(GM1.means_, file=f)
    print('sigma: ', file=f)
    print(GM1.covariances_, file=f)
    print('------------------------------------------', file=f)
    print('x2', file=f)
    print('pi: ', file=f)
    print(GM2.weights_, file=f)
    print('mu: ', file=f)
    print(GM2.means_, file=f)
    print('sigma: ', file=f)
    print(GM2.covariances_, file=f)

#EXECUTE
main()
