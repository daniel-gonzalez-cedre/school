from scipy.special import comb
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

def graph_run(Y1, Y2, confidence, filename):
    fig, ax = plt.subplots()
    ax.fill_between(range(1, 101), [confidence[0] for i in range(1, 101)], [confidence[1] for i in range(1, 101)], alpha=0.25, label='confidence')
    ax = sns.scatterplot(x=range(1, 101), y=Y1, label='original')
    ax = sns.scatterplot(x=range(1, 101), y=Y2, label='modified')
    plt.xlabel('$n$')
    plt.ylabel(r'$\rho_4$')
    legend = ax.legend(loc='lower right')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_chi(Q, confidence, filename):
    fig, ax = plt.subplots()
    ax.fill_between(range(1, 101), [confidence[0] for i in range(1, 101)], [confidence[1] for i in range(1, 101)], alpha=0.25, label='confidence')
    ax = sns.scatterplot(x=range(1, 101), y=Q, label='Q')
    plt.xlabel('$n$')
    plt.ylabel(r'$Q$')
    legend = ax.legend(loc='center right')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_coin():
    return

def graph_X(filename):
    fig, ax = plt.subplots()
    ax = sns.lineplot(x=range(1, 31), y=[comb(2*n, n, exact=True)*pow(pow(0.5, n), 2)/(2*n-1) for n in range(1, 31)], label='density')
    plt.xlabel('$n$')
    plt.ylabel(r'$\mathbb{P}(X = 2n)$')
    legend = ax.legend(loc='upper right')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')
    

def main():
    #ρ = 
    #ρ_mod = 
    #indep_ρ = 
    #indep_ρ_mod = 
    #ρ_confidence = 
    #Qs = 
    #Q_confidence = 

    #graph_run(ρ, ρ_mod, ρ_confidence, 'run_test')
    #graph_run(indep_ρ, indep_ρ_mod, ρ_confidence, 'indep_run_test')
    #graph_chi(Qs, Q_confidence, 'chi_square')

    graph_X("X")

main()
