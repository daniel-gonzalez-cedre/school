# PYTHON SCRIPT TO SEGMENT VIDEO FRAMES BASED ON INTENSITY.
from skimage import measure
from skimage.transform import rescale, resize
from scipy import ndimage
import os
import warnings
import cv2 as cv
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.patches as patches
sns.set(style='ticks', palette='Set2')
#np.set_printoptions(threshold=np.inf)

# ADAPTIVE CROPPING - DESCRIBE THIS IN MORE DETAIL
def crop(img):
    rows, cols = img.shape
    img = 255 - cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 25, 20)
    mid = rows//3
    while np.sum(img[mid - 15:mid + 16,:]) != 0:
        mid = mid + 1
    return img[mid:rows,:].copy()

# TRIM ZEROS AROUND A 2D ARRAY
def trim(img):
    rows, cols = img.shape
    x1, y1, x2, y2 = (1, 1, rows, cols)
    while np.sum(np.square(img[x1 - 1:x1,:])) == 0:
        x1 = x1 + 1
    while np.sum(np.square(img[x2 - 1:x2,:])) == 0:
        x2 = x2 - 1
    while np.sum(np.square(img[:,y1 - 1:y1])) == 0:
        y1 = y1 + 1
    while np.sum(np.square(img[:,y2 - 1:y2])) == 0:
        y2 = y2 - 1
    return img[x1:x2,y1:y2]

def find_bboxes(features, lower, upper):
    #bboxes = []
    #for f in features:
    #    if lower < f.bbox_area and f.bbox_area < upper:
    #        bboxes.append(f.bbox)
    return [f.bbox for f in features if lower < f.bbox_area and f.bbox_area < upper]

def plot_bboxes(img, features, lower, upper):
    bboxes = []
    fig, ax = plt.subplots()
    ax.imshow(img, cmap=plt.cm.gray)
    for f in features:
        if lower < f.bbox_area and f.bbox_area < upper:
            bboxes.append(f.bbox)
            x1, y1, x2, y2 = f.bbox
            y, x = f.centroid
            rect = patches.Rectangle((y1, x1), y2 - y1, x2 - x1, linewidth=1, edgecolor='r', fill=False)
            ax.add_patch(rect)
            ax.plot(x, y, '.g', markersize=1)
    plt.show()
    return bboxes

def classify(img, T):
    imgcrop = crop(img)
    imgbin = 255 - cv.adaptiveThreshold(imgcrop, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 25, 20)
    imgbin = cv.dilate(imgbin, np.ones((9, 9)), iterations=1)

    labels = measure.label(imgbin, 8)
    features = measure.regionprops(labels)

    #bboxes = plot_bboxes(imgcrop, features, 2000, 8000, plot=False)
    bboxes = find_bboxes(features, 2000, 8000)

    if len(bboxes) != 2:
        raise Exception('the number of connected components is', len(bboxes), 'instead of 2')

    prob = {}
    s = ''
    for (x1, y1, x2, y2) in bboxes:
        imgslice = trim(imgcrop[x1:x2,y1:y2].astype(np.float32))
        corr = {}
        for key in T:
            t = 2*T[key].astype(np.float32) - 1
            t = resize(t, imgslice.shape, anti_aliasing=False)
            corr.update({key : ndimage.correlate(imgslice, t, mode='constant')})
        #cmin = abs(np.min([np.max(corr[key]) for key in corr]))
        cmax = np.max([np.max(corr[key]) for key in corr])
        prob.update({key : np.max(corr[key]/cmax) for key in corr if np.max(corr[key]/cmax) == 1.0})
        for key in prob:
            s = s + '\n' + str(key) + '\t' + str(prob[key]) + ('\t\t<-' if prob[key] >= 0.9 else '')
    return prob, s

def main():
    # READ IMAGE IN GRAYSCALE
    #img = cv.imread('../data1/frame050.png', 0)
    #img = cv.imread('../data1/frame100.png', 0)
    #img = cv.imread('../data1/frame170.png', 0)

    #img = cv.imread('../data2/frame010.png', 0)
    #img = cv.imread('../data2/frame050.png', 0)
    #img = cv.imread('../data2/frame100.png', 0)
    #img = cv.imread('../data2/frame150.png', 0)
    #img = cv.imread('../data2/frame184.png', 0)

    T = {'00' + str(key) : np.load('../font-templates/times-new-roman-00' + str(key) + '.npy') for key in range(1, 10)}
    T.update({'0' + str(key) : np.load('../font-templates/times-new-roman-0' + str(key) + '.npy') for key in range(10, 26)})
    T.update({'L' + str(key) : np.load('../font-templates/helvetica-L' + str(key) + '.npy') for key in range(1, 6)})
    T.update({'R' + str(key) : np.load('../font-templates/helvetica-R' + str(key) + '.npy') for key in range(1, 6)})

    #count = 1
    for i in range(1, 185):
        i = str(i)
        while len(i) < 3:
            i = '0' + i
        img = cv.imread('../data2/frame' + i + '.png', 0)
        prob, s = classify(img, T)
        #print(s)
        probs = [(key, value) for key, value in prob.items() if value == 1.0]
        #result = []
        print(i)
        print('\t', probs)
        #if len(probs) != 2:
        #    print('\t' + 'THERE WAS A PROBLEM')
        #else:
        #    result.append(key)
        #for key, value in probs:
        #    print('\t', key, ':\t', value)
        #if count > 5:
        #    exit()
        #count = count + 1
        #exit()

with warnings.catch_warnings():
    warnings.simplefilter('ignore')
    main()
