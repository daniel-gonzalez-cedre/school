from skimage import measure
import os
import cv2 as cv
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

def histogram_plot(img, title, filename):
    fig, ax = plt.subplots()
    ax.hist(img.flatten(), bins=256, density=True)
    if not os.path.exists('./figures'):
        os.makedirs('./figures')
    plt.title(title)
    plt.xlabel('Intensity')
    plt.ylabel('Probability')
    plt.savefig('./figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

def cdf_plot(img, title, filename):
    F = cdf(img)
    fig, ax = plt.subplots()
    ax.plot(range(0, 255), [F[x] for x in range(0, 255)])
    if not os.path.exists('./figures'):
        os.makedirs('./figures')
    plt.title(title)
    plt.xlabel('Intensity')
    plt.ylabel('CDF')
    plt.savefig('./figures/' + filename + '.pdf', format='pdf', dpi=1000, bbox_inches='tight')

# COMPUTES THE HISTOGRAM OF AN 8-BIT GRAYSCALE IMAGE
def histogram(img):
    N = img.shape[0] * img.shape[1]
    return np.asarray([len(img[img == val]) / N for val in range(0, 256)])

# COMPUTES THE CDF OF AN IMAGE'S INTENSITY DISTRIBUTION
def cdf(img):
    hist = histogram(img)
    cdf = np.asarray([np.sum(hist[:i + 1]) for i in range(0, len(hist))])
    return cdf

# HISTOGRAM EQUALIZATION USING THE CDF
def histogram_eq(img):
    F = cdf(img)
    eq = np.array([F[p]*255 for p in img], dtype=np.uint8)
    return eq
