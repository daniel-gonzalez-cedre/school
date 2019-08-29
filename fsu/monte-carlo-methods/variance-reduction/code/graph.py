from scipy.special import comb
import math
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

def graph_mean(N, crude, anti, control, filename):
    fig, ax = plt.subplots()
    ax = sns.lineplot(x=N, y=[(math.e - 1) for n in N], dashes=True, label='True Value')
    ax = sns.lineplot(x=N, y=crude, label='Crude')
    ax = sns.lineplot(x=N, y=anti, label='Antithetic')
    ax = sns.lineplot(x=N, y=control, label='Control')
    ax.lines[0].set_linestyle('--')
    ax.set(xticks=N)
    plt.xlabel('$N$')
    legend = ax.legend(loc='best')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_var(N, crude, anti, control, filename):
    fig, ax = plt.subplots()
    ax = sns.lineplot(x=N, y=crude, label='Crude')
    ax = sns.lineplot(x=N, y=anti, label='Antithetic')
    ax = sns.lineplot(x=N, y=control, label='Control')
    ax.lines[2].set_linestyle('--')
    ax.set(xticks=N)
    plt.xlabel('$N$')
    legend = ax.legend(loc='best')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_error(N, crude, anti, control, filename):
    fig, ax = plt.subplots()
    ax = sns.lineplot(x=N, y=crude, label='Crude')
    ax = sns.lineplot(x=N, y=anti, label='Antithetic')
    ax = sns.lineplot(x=N, y=control, label='Control')
    ax.set(xticks=N)
    plt.xlabel('$N$')
    legend = ax.legend(loc='best')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def main():
    N = [n*pow(10, 4) for n in [1, 2, 3, 4, 5]]
    mean_crude = [1.7163427216379707, 1.7224683092151092, 1.7175469454614931, 1.7195327326676335, 1.716042951088645]
    mean_anti = [1.7190759180648933, 1.7181647551000991, 1.7182807406143692, 1.7181387743301026, 1.7181811210019788]
    mean_control = [1.71933720483377, 1.7182157514461505, 1.718001184306902, 1.7177462170967643, 1.7185802225173399]
    graph_mean(N, mean_crude, mean_anti, mean_control, 'mean')

    var_crude = [0.24070640733321344, 0.2449467540827154, 0.24209748817550245, 0.2414545211639719, 0.2410606609642642]
    var_anti = [0.00399766851668589, 0.003920373105039708, 0.0039054819807029404, 0.0039055986498623975, 0.003928181937815285]
    var_control = [0.0040055006510773625, 0.003923870045177055, 0.003931420758714026, 0.0039044745951596137, 0.0039427080538887]
    graph_var(N, var_crude, var_anti, var_control, 'var')

    θ = math.e - 1
    error_crude = [abs(θ - m) for m in mean_crude]
    error_anti = [abs(θ - m) for m in mean_anti]
    error_control = [abs(θ - m) for m in mean_control]
    graph_error(N, error_crude, error_anti, error_control, 'error')
    
main()
