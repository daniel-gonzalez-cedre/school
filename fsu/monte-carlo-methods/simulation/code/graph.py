from scipy.special import comb
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

def graph(X1, X2, T, filename):
    fig, ax1 = plt.subplots()
    ax1.fill_between(range(1, 101), [0 for i in range(1, 101)], [T[0] for i in range(1, 101)], alpha=0.25)
    ax1.fill_between(range(1, 101), [0 for i in range(1, 101)], [T[1] for i in range(1, 101)], alpha=0.25)
    ax1.fill_between(range(1, 101), [0 for i in range(1, 101)], [T[2] for i in range(1, 101)], alpha=0.25)
    ax1.fill_between(range(1, 101), [0 for i in range(1, 101)], [T[3] for i in range(1, 101)], alpha=0.25)
    ax1.fill_between(range(1, 101), [0 for i in range(1, 101)], [T[4] for i in range(1, 101)], alpha=0.25)
    ax1 = sns.scatterplot(x=range(1, 101), y=X1[0], label='Box-Muller', color='#7dbfa7')
    ax1 = sns.scatterplot(x=range(1, 101), y=X2[0], label='Beasley-Springer-Moro', color='#ee926b')
    ax2 = ax1.twinx()
    ax1.set_xlabel('n')
    ax1.set_yticks(T)
    ax1.set_yticklabels(['15%', '10%', '5%', '2.5%', '1%'])
    plt.xlabel('$n$')
    legend = ax1.legend(loc='best')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def main():
    T     = [1.610, 1.933, 2.492, 3.070, 3.857]
    bm    = [[float(x) for x in line.strip('\n').split('\t')] for line in open('../data/box-muller.dat')]
    bsm   = [[float(x) for x in line.strip('\n').split('\t')] for line in open('../data/beasley-springer-moro.dat')]
    graph(bm, bsm, T, 'normality')
    
main()
