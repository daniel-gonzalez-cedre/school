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
    ρ = [-0.423728813559322, -0.0196078431372549, 0.0, -0.07142857142857142, -0.0196078431372549, -0.16666666666666666, -0.49019607843137253, -0.8181818181818182, -0.4901960784    3137253, -0.07142857142857142, -0.19047619047619047, -0.0196078431372549, -0.07142857142857142, -0.8, -0.49019607843137253, -0.6428571428571429, -0.02857142857142857, -0.071428    57142857142, -0.47368421052631576, -0.0196078431372549, -0.0196078431372549, -0.09090909090909091, -0.07142857142857142, -0.10843373493975904, -0.16666666666666666, -0.44444444    44444444, -0.9, 0.0, -0.09090909090909091, -0.16666666666666666, -0.09090909090909091, -0.6428571428571429, -0.16666666666666666, -0.4444444444444444, 0.0, -0.1, -0.16666666666    666666, -0.0196078431372549, -0.16666666666666666, 0.0, -0.16666666666666666, -0.47368421052631576, 0.0, -0.0196078431372549, -0.8181818181818182, -0.16666666666666666, -0.0196    078431372549, -0.5517241379310345, -0.2571428571428571, -0.09090909090909091, -0.8181818181818182, 0.0, -0.09090909090909091, -0.9, -0.7142857142857143, 0.0, -0.9, -0.090909090    90909091, -0.47368421052631576, -0.8181818181818182, -0.49019607843137253, -0.8181818181818182, -0.16666666666666666, -0.16666666666666666, -0.02857142857142857, 0.0, -0.444444    4444444444, 0.0, -0.09090909090909091, -0.05263157894736842, -0.16666666666666666, -1.0, -0.9, -0.7142857142857143, 0.0, -0.16666666666666666, -0.9, -0.16666666666666666, -0.01    96078431372549, -0.09090909090909091, -0.06474820143884892, -0.47368421052631576, -0.19047619047619047, -0.0196078431372549, -0.01694915254237288, -0.23222748815165878, -0.2571    428571428571, -0.25252525252525254, -0.8181818181818182, -0.16666666666666666, -0.02857142857142857, 0.0, -0.09090909090909091, -0.07142857142857142, -0.0196078431372549, -0.19    047619047619047, -0.09090909090909091, -0.01694915254237288, -0.16666666666666666, -0.09090909090909091]
    ρ_mod = [-0.09090909090909091, -0.05263157894736842, -0.09090909090909091, -0.2571428571428571, -0.3333333333333333, -0.13432835820895522, -0.8181818181818182, -0.264705882    3529412, -0.13432835820895522, -0.09090909090909091, -0.2571428571428571, -0.13432835820895522, -0.13432835820895522, -0.09090909090909091, 0.0, -0.8, -0.3333333333333333, -0.1    3432835820895522, -0.2, -0.13432835820895522, 0.0, -0.09090909090909091, -0.423728813559322, -0.423728813559322, -0.13432835820895522, -0.1111111111111111, -0.0196078431372549,     -0.423728813559322, -0.0196078431372549, -0.2, -0.2, -0.20930232558139536, -0.4444444444444444, -0.0196078431372549, -0.2, -0.0196078431372549, -0.47368421052631576, -0.818181    8181818182, -0.09090909090909091, -0.09090909090909091, -0.09090909090909091, -0.5, -0.13432835820895522, -0.1111111111111111, -0.2, -0.1111111111111111, -0.13432835820895522,     -0.2, -0.3333333333333333, -0.09090909090909091, -0.2647058823529412, -0.8181818181818182, -0.1111111111111111, -0.2, -0.0196078431372549, -0.2, -0.423728813559322, -0.09090909    090909091, -0.13432835820895522, -0.4444444444444444, -0.1111111111111111, -0.13432835820895522, -0.423728813559322, -0.2, -0.13432835820895522, -0.2, -0.13432835820895522, -0.    09090909090909091, -0.2, -0.2, -0.2, -0.3333333333333333, -0.09090909090909091, 0.0, -0.47368421052631576, -0.3333333333333333, -0.2, -0.09090909090909091, -0.2647058823529412,     -0.0196078431372549, -0.1111111111111111, -0.3333333333333333, -0.13432835820895522, -0.0196078431372549, -0.2, -0.2, -0.13432835820895522, -0.494949494949495, -0.2, -0.134328    35820895522, -0.494949494949495, -0.09090909090909091, -0.1111111111111111, -0.3333333333333333, -0.2, -0.09090909090909091, -0.7142857142857143, -0.09090909090909091, -0.33333    33333333333, -0.4444444444444444]
    indep_ρ = [-0.08544726301735647, -0.02632808848730332, -0.05863192182410423, -0.015570384493168096, -0.0005333333333333334, -0.006075334143377886, -0.00043649061545176777,     -0.0008539709649871904, -0.0996895481200414, -0.042007001166861145, -0.0002533569799847986, -0.011795543905635648, -0.01264516129032258, -0.08861756597085467, -0.00337552742616    03376, -0.04076497232008052, -0.017777777777777778, -0.03506230078238192, -0.12424075096631695, -0.11076923076923077, -0.11986727498963086, -0.0002952465308532625, -0.024317021    91534074, -0.001221001221001221, -0.015570384493168096, -0.07870067582297798, -0.004273504273504274, 0.0, -0.00026518164942985947, -0.017481270067784518, -0.0003075976622577668    6, -0.001182033096926714, -0.03676694013977515, -0.04775360271263069, -0.3618843683083512, 0.0, -0.028733593472862716, -0.15339130434782608, -0.054505005561735265, -0.000238379    02264600716, -0.002932551319648094, -0.0015360983102918587, -0.06206896551724138, -0.062403300670448685, -0.02069857697283312, -0.0003619254433586681, -0.21141649048625794, -0.    004197271773347324, -0.013569648296870672, -0.00196078431372549, -0.022570244127130355, -0.01699618453000347, -0.001968934587617589, -0.02192393736017897, -0.008151287903488751    , -0.006232859636000997, -0.06870229007633588, -0.0002904443799012489, -0.0015600624024961, -0.02030456852791878, -0.022706630336058128, -0.002589928057553957, -0.0128388017118    40228, -0.092776886035313, -0.03257918552036199, -0.004910626595953644, -0.002896684905053106, -0.024390243902439025, -0.04841936774709884, -0.001597444089456869, -0.0314341846    7583497, -0.033550792171481825, -0.07302231237322515, -0.007901668129938543, -0.008460236886632826, -0.05370193835398793, -0.16129032258064516, -0.0012836970474967907, -0.01630    98878695209, -0.03596403596403597, -0.0039447731755424065, -0.020806794055201697, -0.0027683789603199014, -0.10358056265984655, -0.15643845335225257, -0.04645880652488127, -0.0    08547008547008548, -0.0005497526113249038, -0.024390243902439025, -0.007689941556444171, -0.0006891798759476223, -0.0026954177897574125, -0.014492753623188406, -0.1248710010319    9174, -0.052478134110787174, -0.11001100110011001, -0.020234823882088433, -0.00019924287706714485, -0.22703207723450639, -0.00020614306328592042]
    indep_ρ_mod = [-0.17100868403473615, -0.2546397694524496, -0.0940098060115114, -0.013845719129697655, -0.11509511427398385, -0.29300968298182783, -0.14276014259039213, -0.1    1909795630725863, -0.11432229742088897, -0.12532523850823937, -0.15010006671114076, -0.08658985627746764, -0.2884238064094179, -0.017238922923493376, -0.0987205812667825, -0.08    706905476757429, -0.06714761376248612, -0.10800069120442371, -0.19780971937029432, -0.038102643856920686, -0.03948180135718692, -0.2760113449768622, -0.33624295326422987, -0.03    466338006470498, -0.030265596046942556, -0.04961240310077519, -0.0698124153935409, -0.02701212789415656, -0.15480172001911133, -0.036488027366020526, -0.19817589576547232, -0.1    2828727806701376, -0.11069261351747227, -0.07870067582297798, -0.34372969460688757, -0.10582010582010581, -0.23446658851113716, -0.19185220274751302, -0.08075978808631606, -0.0    9874055415617128, -0.08600522911793038, -0.30287859824780977, -0.14619289340101524, -0.1546216101093284, -0.09574468085106383, -0.20164609053497942, -0.13060278207109738, -0.05    3409720938828315, -0.13927612226627445, -0.18859138533178113, -0.22300048867893793, -0.1706021251475797, -0.17614360162130863, -0.11602004826434008, -0.08600522911793038, -0.15    39912005028284, -0.003973931012557622, -0.1166936790923825, -0.006257822277847309, -0.1810815903523648, -0.12318840579710146, -0.023435986829362775, -0.20771001150747986, -0.14    6033350176857, -0.03948180135718692, -0.0031620553359683794, -0.08089922006423, -0.15627705627705626, -0.009317360714964822, -0.1275324979505797, -0.14746543778801843, -0.13037    579704246371, -0.007240547063555913, -0.1579626047711154, -0.19372840818495882, -0.16623909697280656, -0.11870794078061911, -0.17866909753874202, -0.12915921288014312, -0.14159    407099206864, -0.08159802560542959, -0.1534018875898014, -0.05589100479950457, -0.09523083955508152, -0.1232876712328767, -0.1852708694813958, -0.050975456261799876, -0.0999306    0374739764, -0.18, -0.27965396772583595, -0.22900432900432902, -0.06277463904582549, -0.0513595166163142, -0.17146684527796383, -0.18015482054890922, -0.24901638171543028, -0.0    9135135135135135, -0.10493738304304016, -0.127163280662152, -0.099601593625498]
    ρ_confidence = [-0.21417223122266885, 0.19397021102064863]#Qs = 
    Qs = [87.39333333333335, 83.56333333333335, 80.52000000000001, 92.97666666666667, 87.87666666666668, 84.30333333333334, 82.45333333333335, 85.20666666666668, 82.47000000000    001, 80.12666666666667, 85.62666666666668, 84.27666666666669, 91.26666666666667, 84.22666666666667, 75.34000000000002, 106.48666666666668, 78.57666666666668, 79.41333333333334,     92.55333333333334, 80.19666666666667, 86.97666666666667, 108.03333333333335, 78.38666666666668, 76.83666666666667, 93.21666666666668, 73.94666666666667, 79.69666666666667, 82.    73666666666668, 91.78666666666668, 86.59333333333335, 89.63666666666668, 90.27666666666669, 87.42333333333335, 75.07666666666668, 92.73666666666668, 81.68, 82.36666666666667, 8    4.90666666666668, 84.57666666666668, 78.49666666666668, 85.85666666666668, 83.47666666666667, 83.45666666666668, 79.98333333333335, 77.51333333333335, 90.50666666666667, 81.263    33333333335, 75.56333333333335, 84.54666666666668, 86.83666666666667, 92.70333333333335, 76.35666666666668, 89.76, 90.59666666666668, 74.67666666666668, 83.26333333333335, 79.7    2333333333334, 88.14333333333335, 91.65333333333335, 80.33666666666667, 83.32666666666668, 87.97333333333334, 80.72666666666667, 78.09333333333335, 93.53333333333335, 86.206666    66666668, 84.81333333333335, 73.00333333333334, 94.26666666666668, 84.17666666666668, 85.78666666666668, 81.89333333333335, 96.25666666666667, 85.61666666666667, 89.42000000000    002, 69.53333333333335, 87.29666666666668, 76.66000000000001, 82.57333333333335, 93.00333333333334, 83.12666666666668, 93.74333333333334, 79.07333333333335, 89.85333333333334,     76.87333333333335, 97.17333333333335, 89.26666666666668, 82.42666666666668, 96.33666666666667, 83.90666666666668, 85.65333333333335, 81.42333333333335, 82.46333333333335, 76.37    333333333335, 85.58333333333334, 94.62666666666668, 82.90666666666668, 81.73333333333335, 84.91666666666669, 89.31333333333335]
    Q_confidence = [0.352, 7.815]

    graph_run(ρ, ρ_mod, ρ_confidence, 'run_test')
    graph_run(indep_ρ, indep_ρ_mod, ρ_confidence, 'indep_run_test')
    graph_chi(Qs, Q_confidence, 'chi_square')
    graph_X("X")

main()
