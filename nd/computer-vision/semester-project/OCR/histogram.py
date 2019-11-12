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

# SIMPLE RANGE-BASED THRESHOLDING
def threshold(img, lower, upper):
    return cv.inRange(img, np.asarray([lower]), np.asarray([upper]))

def integral(img):
    rows, cols = img.shape
    return np.reshape(np.asarray([np.sum(img[0:i + 1, 0:j + 1]) for i in range(0, rows) for j in range(0, cols)]), (rows, cols))

# ADAPTIVE THRESHOLDING: Bradley & Roth - 'Adaptive Thresholding using the Integral Image'
def adaptive_threshold(img, dim, t):
    rows, cols = img.shape
    integ = integral(img)
    result = img.copy()

    for i in range(rows):
        for j in range(cols):
            x1 = int(max(i - dim/2, 0))
            x2 = int(min(i + dim/2, rows - 1))
            y1 = int(max(j - dim/2, 0))
            y2 = int(min(j + dim/2, cols - 1))
            count = (x2 - x1)*(y2 - y1)
            s = integ[x2, y2] - integ[x2, y1 - 1] - integ[x1 - 1, y2] + integ[x1 - 1, y1 - 1]
            if img[i, j]*count <= s*(100 - t)/100:
                result[i, j] = 0
            else:
                result[i, j] = 255
    return result
