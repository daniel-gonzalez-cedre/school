from scipy.special import comb
import random
import numpy as np

def significance(s = 0.05):
    n = 1
    P = 1
    while True:
        p = comb(2*n, n, exact=True)*pow(pow(0.5, n), 2)/(2*n-1)
        P = P - p
        if P < s:
            break
        n += 1
    return n

def X_test():
    success, failure, count = (0, 0, 0)
    while True:
        count += 1
        if random.random() >= 0.5:
            success += 1
        else:
            failure += 1
        if success == failure:
            break
    return (not count >= 128, count)

def X_tests(n = 100):
    accepts, rejects = (0, 0)
    counts = []
    for i in range(0, n):
        result, count = X_test()
        if result:
            accepts += 1
        else:
            rejects += 1
        counts.append(count)
    return (accepts, rejects, np.mean(counts), np.median(counts))

def main():
    accepts, rejects, μX, mX = X_tests()
    print('Number of times accepted: ' + str(accepts))
    print('Number of times rejected: ' + str(rejects))
    print('Average value of X: ' + str(μX))
    print('Median value of X: ' + str(mX))

main()
