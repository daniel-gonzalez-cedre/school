# PYTHON SCRIPT TO SEGMENT VIDEO FRAMES BASED ON INTENSITY
from skimage import measure
import os
import cv2 as cv
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

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

# adaptive cropping - describe this in more detail
def adaptive_crop(img):
    total = np.sum(img)
    rows, cols = img.shape
    line = rows
    while True:
        ratio = np.sum(img[line:rows,:]) / total
        print(ratio)
        #if ratio >= 0.55:
        #    line = line + line//2
        #elif ratio <= 0.4:
        #    line = line - line//2
        if ratio >= 0.4:
            line = line + line//2
        elif ratio <= 0.35:
            line = line - line//2
        else:
            return img[line:rows,:]

def main():
    # READ IMAGE IN GRAYSCALE
    img = cv.imread('./data1/frame050.png', 0)
    #img = cv.imread('./data1/frame100.png', 0)
    #img = cv.imread('./data1/frame170.png', 0)

    #img = cv.imread('./data2/frame050.png', 0)

    rows, cols = img.shape

    cv.imshow('img', img)
    cv.waitKey(0)

    #ada = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 101, 20)
    #cv.imshow('ada', ada)
    #cv.waitKey(0)

    #integ = integral(img)
    ker = np.ones((3, 3), dtype=np.uint8)
    imgbin = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 25, 20)
    imgbin = 255*np.ones(imgbin.shape, dtype=np.uint8) - imgbin
    #imgbin = cv.erode(imgbin, ker, iterations=1)
    imgbin = cv.dilate(imgbin, ker, iterations=1)

    # CROP IMAGE
    #imgcrop = imgbin[rows//2:rows,:]
    imgcrop = adaptive_crop(imgbin)

    #print(np.sum(imgbin))
    #print(np.sum(imgcrop))
    #print(np.sum(imgcrop) / np.sum(imgbin))

    cv.imshow('binary image', imgcrop)
    cv.waitKey(0)

    labels = measure.label(imgcrop, 4)
    features = measure.regionprops(labels)
    print("I found %d objects in total." % (len(features)))
    
    
    his = []
    for i in range(0, len(features)):
        #if features[i].minor_axis_length > 0:
        #    his.append(features[i].major_axis_length / features[i].minor_axis_length)
        his.append(features[i].bbox)
    his.sort()
    print(his)
    #plt.hist(his)
    #plt.xlabel("Ratio")
    #plt.ylabel("Count")
    #plt.show()

    #for f in features:
    #    plt.imshow(f.image)
    #    plt.show()
    fig, ax = plt.subplots()
    ax.imshow(imgcrop, cmap=plt.cm.gray)
    for i in range(0, len(his)):
        #if abs(his[i] - 1.8) < 0.5 or abs(his[i] - 2.5) < 0.5 or abs(his[i] - 2.8) < 0.5:
        #    y, x = features[i].centroid
        #    ax.plot(x, y, '.g', markersize=10)
        x1, y1, x2, y2 = his[i]
        ratio = (x2 - x1)/(y2 - y1)
        if abs(ratio - 1.8) < 0.5 or abs(ratio - 2.5) < 0.5 or abs(ratio - 2.8) < 0.5:
            #plt.imshow(features[i].image)
            #plt.show()
            y, x = features[i].centroid
            ax.plot(x, y, '.g', markersize=10)
        #if his[i] <= fThr:
        #    squares = squares + 1
        #    y, x = features[i].centroid
        #    ax.plot(x, y, '.g', markersize=10)
        #else:
        #    cashews = cashews + 1
        #    y, x = features[i].centroid
        #    ax.plot(x, y, '.b', markersize=10)
    plt.show()

    ## CONSTRUCT INTENSITY-BASED MASK
    #mask = threshold(small, 0, 150)

    ## DISPLAY MASK
    #cv.imshow('mask', mask)
    #cv.waitKey(0)

    #cv.imshow('new', mask * imgcrop
    #cv.waitKey(0)

main()
