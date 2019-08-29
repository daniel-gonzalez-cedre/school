import math
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from scipy.stats import norm
sns.set(style='ticks', palette='Set2')

π = np.pi
sin = np.sin
cos = np.cos

def graph_sphere_plane(filename):
    r = 1
    φ, θ = np.mgrid[0.0:π:100j, 0.0:2.0*π:100j]
    x = r*sin(φ)*cos(θ)
    y = r*sin(φ)*sin(θ)
    z = r*cos(φ)

    a, b, c, d = 0, 0, 1, 0
    X = np.linspace(-1, 1, 10)
    Y = np.linspace(-1, 1, 10)

    X, Y = np.meshgrid(X, Y)
    Z_3 = (-0.75 - a*X - b*Y)/c
    Z_2 = (-0.5 - a*X - b*Y)/c
    Z_1 = (-0.25 - a*X - b*Y)/c
    Z0 = (0 - a*X - b*Y)/c
    Z1 = (0.25 - a*X - b*Y)/c
    Z2 = (0.5 - a*X - b*Y)/c
    Z3 = (0.75 - a*X - b*Y)/c

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(x, y, z, rstride=1, cstride=1, alpha=0.7, linewidth=0)
    ax.plot_surface(X, Y, Z_3, rstride=1, cstride=1, alpha=0.2, linewidth=0)
    ax.plot_surface(X, Y, Z_2, rstride=1, cstride=1, alpha=0.2, linewidth=0)
    ax.plot_surface(X, Y, Z_1, rstride=1, cstride=1, alpha=0.2, linewidth=0)
    ax.plot_surface(X, Y, Z0, rstride=1, cstride=1, alpha=0.2, linewidth=0)
    ax.plot_surface(X, Y, Z1, rstride=1, cstride=1, alpha=0.2, linewidth=0)
    ax.plot_surface(X, Y, Z2, rstride=1, cstride=1, alpha=0.2, linewidth=0)
    ax.plot_surface(X, Y, Z3, rstride=1, cstride=1, alpha=0.2, linewidth=0)
    ax.contour(x, y, z, alpha=1)
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def graph_normal(data1, data2, mean, std, filename):
    fig, ax = plt.subplots()
    xmin = np.min([np.min(data1), np.min(data2)])
    xmax = np.max([np.max(data1), np.max(data2)])
    x = np.linspace(xmin, xmax, 200)
    y = norm.pdf(x, mean, std)
    z1 = norm.pdf(x, np.mean(data1), np.std(data1))
    z2 = norm.pdf(x, np.mean(data2), np.std(data2))
    ax.plot(x, y, label=r'$\mathcal{N}(0, 1)$')
    ax.plot(x, z1, label='MarsagliaSample')
    ax.plot(x, z2, label='AntitheticSample')
    legend = ax.legend(loc='best')
    plt.savefig('../figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

data8_1 = [-0.623137, 0.11398, -0.623137, -2.14955, -1.51021, -1.40924, 1.44578, 2.26981, 4.3577, 6.11874, 5.70193, 6.068, 6.65802, 8.72204, 7.45114, 7.96403]
data8_2 = [0.572388, 0.441094, 0.572388, -1.01789, -1.27285, -2.61051, -2.25728, -1.48246, 0.96338, 1.13852, 0.96338, 1.87546, 1.11724, 1.16837, 1.04909, 1.25388]
data10_1 = [-1.44206, -1.00632, -1.44206, -2.73681, -2.11529, -1.46554, 0.394395, 0.467234, 0.345231, 0.7608, 0.540328, 0.266629, 1.58542, 3.00233, 3.11231, 3.44401, 4.1442, 3.57456, 4.72686, 5.39585]
data10_2 = [1.16826, 0.981416, 1.16826, 0.42457, 1.24968, 1.21038, 1.57343, 2.36519, 2.35969, 2.14284, -2.15624, -2.15696, -2.15624, -2.15569, -2.15796, -2.15763, -2.16024, -2.15963, -2.15851, -2.15708]
data20_1 = [-0.271842, 0.562998, -0.271842, 0.375009, 0.159457, -1.63881, -3.70714, -2.90141, -3.65962, -2.90485, -3.78523, -2.73462, -2.51102, -2.53937, -0.795555, 0.0129465, 0.387947, 0.475, 1.05713, 2.13523, 1.2418, 1.32411, 0.642432, 0.0638055, -0.85537, -1.15261, -0.575869, 0.43004, 0.953137, 0.495757, 0.693261, 1.21181, 2.24134, 3.22742, 4.5665, 5.33383, 5.13882, 4.56222, 4.13398, 4.74401]
data20_2 = [0.0453444, -0.108021, 0.0453444, 0.581295, -1.66567, -1.63554, -2.28179, -1.2425, -0.951559, -0.869593, -0.306462, 0.611038, 1.25969, 0.318716, -0.191979, 0.792859, 2.4916, 2.66014, 2.8549, 2.24325, -0.784025, -0.810065, -0.784025, -0.785639, -0.794555, -0.793294, -0.778385, -0.796171, -0.797971, -0.806677, -0.793038, -0.779247, -0.784471, -0.772799, -0.768327, -0.756983, -0.748037, -0.7385, -0.734287, -0.734197]
mean = 0
std = 1
graph_normal(data20_1, data20_2, mean, std, 'normal')









