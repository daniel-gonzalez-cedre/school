import random
import numpy as np

def mersenne_twister(n):
    return [random.random() for x in range(0, n)]

def run_ups(seq):
    length = 1
    u1, u2, u3, u4 = (0, 0, 0, 0)
    prev = seq[0]
    for u in seq[1:]:
        if prev <= u:
            length += 1
        else:
            if length == 1:
                u1 += 1
            elif length == 2:
                u2 += 1
            elif length == 3:
                u3 += 1
            else:
                u4 += 1
            length = 1
        prev = u
    if length == 1:
        u1 += 1
    elif length == 2:
        u2 += 1
    elif length == 3:
        u3 += 1
    else:
        u4 += 1
    return u1, u2, u3, u4

def modified_run_ups(seq):
    skip = False
    length = 1
    u1, u2, u3, u4 = (0, 0, 0, 0)
    prev = seq[0]
    for u in seq[1:]:
        if skip:
            prev = u
            length = 0
            skip = False
        if prev <= u:
            length += 1
            prev = u
        else:
            if length == 1:
                u1 += 1
            elif length == 2:
                u2 += 1
            elif length == 3:
                u3 += 1
            else:
                u4 += 1
            skip = True
    if length == 1:
        u1 += 1
    elif length == 2:
        u2 += 1
    elif length == 3:
        u3 += 1
    else:
        u4 += 1
    return u1, u2, u3, u4

def serial_correlation(runs):
    u1, u2, u3, u4 = runs
    s = pow(u1 + u2 + u3 + u4, 2)
    return (4*(u1*u2 + u2*u3 + u3*u4 + u4*u1) - s) / (4*(pow(u1, 2) + pow(u2, 2) + pow(u3, 2) + pow(u4, 2)) - s)

def serial_stats(n = 100, m = 15, verbose = False):
    ρ = [serial_correlation(run_ups(mersenne_twister(m))) for i in range(0, n)]
    ρ_mod = [serial_correlation(modified_run_ups(mersenne_twister(m))) for i in range(0, n)]
    indep_ρ = [serial_correlation(run_ups(mersenne_twister(2*n))) for i in range(0, n)]
    indep_ρ_mod = [serial_correlation(modified_run_ups(mersenne_twister(3*n))) for i in range(0, n)]
    μ = -1/(n-1)
    σ = np.sqrt(pow(n, 2)/(pow(n-1, 2)*(n-2)))
    if verbose:
        stats = 'ρ: \n' + str(ρ) + '\n'\
                + 'ρ_mod: \n' + str(ρ_mod) + '\n'\
                + 'indep_ρ: \n' + str(indep_ρ) + '\n'\
                + 'indep_ρ_mod: \n' + str(indep_ρ_mod) + '\n\n'
    else:
        stats = ''
    stats += 'μ = ' + str(μ) + '\n'\
            + 'σ = ' + str(σ) + '\n'\
            + 'mean: ' + str(np.mean(ρ)) + '\n'\
            + 'std dev: ' + str(np.std(ρ)) + '\n\n'\
            + 'mean modified: ' + str(np.mean(ρ_mod)) + '\n'\
            + 'std dev modified: ' + str(np.std(ρ_mod)) + '\n\n'\
            + 'indep mean: ' + str(np.mean(indep_ρ)) + '\n'\
            + 'indep std dev: ' + str(np.std(indep_ρ)) + '\n\n'\
            + 'indep mean modified: ' + str(np.mean(indep_ρ_mod)) + '\n'\
            + 'indep std dev modified: ' + str(np.std(indep_ρ_mod)) + '\n\n'\
            + 'confidence: (' + str(μ - 2*σ) + ', ' + str(μ + 2*σ) + ')'
    return stats

def chi_squared(k=100, n=300):
    lower, upper = (0.352, 7.815)
    accept, reject = (0, 0)
    Qs = []
    for i in range(0, k):
        Y1, Y2, Y3, Y4 = run_ups(mersenne_twister(n))
        p1, p2, p3, p4 = (1-1/2, 1/2-1/6, 1/6-1/24, 1/24)
        Q = (pow(Y1 - n*p1, 2)/p1 + pow(Y2 - n*p2, 2)/p2 + pow(Y3 - n*p3, 2)/p3 + pow(Y4 - n*p4, 2)/p4)/n
        Qs.append(Q)
        if lower <= Q <= upper:
            accept += 1
        else:
            reject += 1
    return ("Accept", Qs) if accept > reject else ("Reject", Qs)

def main():
    print(serial_stats())
    print('')
    result, Qs = chi_squared()
    print(result)
    print(Qs)

main()
