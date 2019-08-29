import math
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
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
