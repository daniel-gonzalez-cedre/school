import numpy as np

def fibonacci(n):
    f = [1, 1]
    for i in range(0, n-2):
        f.append((f[i] + f[i+1]) % pow(2, 31))
    return f

def kolmogorov_smirnov(seq):
    n = len(seq)
    Dplus = np.max([(k+1) / len(seq) - seq[k] for k in range(0, len(seq))])
    Dminus = np.max([seq[k] - k / len(seq) for k in range(0, len(seq))])
    return max(Dplus, Dminus)

def main():
    print(kolmogorov_smirnov(fibonacci(1000)))

main()
