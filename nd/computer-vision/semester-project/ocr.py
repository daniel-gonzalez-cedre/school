# PYTHON SCRIPT TO SEGMENT VIDEO FRAMES BASED ON INTENSITY
from skimage import measure
import os
import cv2 as cv
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

times_new_roman0 = [\
        ]

def template():
    return 0

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
    ker = np.ones((5, 5), dtype=np.uint8)
    imgbin = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 25, 20)
    imgbin = 255*np.ones(imgbin.shape, dtype=np.uint8) - imgbin
    #imgbin = cv.erode(imgbin, ker, iterations=1)
    #imgbin = cv.dilate(imgbin, ker, iterations=1)

    # CROP IMAGE
    imgcrop = imgbin[rows//2:rows,:]
    #imgcrop = adaptive_crop(imgbin)
    #imgcrop = imgbin

    cv.imshow('binary image', imgcrop)
    cv.waitKey(0)

    labels = measure.label(imgcrop, 8)
    features = measure.regionprops(labels)
    print("I found %d objects in total." % (len(features)))
    
    fig, ax = plt.subplots()
    ax.imshow(imgcrop, cmap=plt.cm.gray)
    #for i in range(0, len(his)):
    for f in features:
        x1, y1, x2, y2 = f.bbox
        ratio = (x2 - x1)/(y2 - y1)
        if abs(ratio - 1.8) < 0.5 or abs(ratio - 2.5) < 0.5 or abs(ratio - 2.8) < 0.5:
            #plt.imshow(features[i].image)
            #plt.show()
            plt.imshow(f.image)
            plt.show()
            y, x = f.centroid
            #ax.plot((x2 - x1)/2, (y2 - y1)/2, '.g', markersize=10)
            ax.plot(x, y, '.g', markersize=10)
    plt.show()

main()
