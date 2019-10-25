# PYTHON SCRIPT TO SEGMENT VIDEO FRAMES BASED ON INTENSITY
from skimage import measure
from skimage.transform import rescale
import os
import warnings
import cv2 as cv
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

times_new_roman0 = [\
        ]

def main():
    # READ IMAGE IN GRAYSCALE
    font = 'helvetica'
    img = cv.imread('./font-templates/' + font + '.png', 0)
    img = 255*np.ones(img.shape) - img
    rows, cols = img.shape

    img[img < 50] = 0
    img[img >= 50] = 255

    #cv.imshow('img', img)
    #cv.waitKey(0)

    labels = measure.label(img, 8)
    features = measure.regionprops(labels)
    print("I found %d objects in total." % (len(features)))

    #fig, ax = plt.subplots()
    #ax.imshow(img, cmap=plt.cm.gray)
    #for f in features:
    #    x1, y1, x2, y2 = f.bbox
    #    plt.imshow(f.image)
    #    plt.show()
    #    y, x = f.centroid
    #    ax.plot(x, y, '.g', markersize=10)
    #plt.show()

    templates = [f.image for f in features]

    with warnings.catch_warnings():
        warnings.simplefilter('ignore')

        np.savetxt('./font-templates/'+ font + '-0.dat', templates[0], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-1.dat', templates[2], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-2.dat', templates[4], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-3.dat', templates[6], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-4.dat', templates[8], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-5.dat', templates[1], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-6.dat', templates[3], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-7.dat', templates[5], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-8.dat', templates[7], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-9.dat', templates[9], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-L.dat', templates[10], fmt='%d')
        np.savetxt('./font-templates/'+ font + '-R.dat', templates[11], fmt='%d')
        #rescaled = rescale(templates[1], 1, anti_aliasing=False)
        #cv.imshow('s', rescaled)
        #cv.waitKey(0)
        #rescaled = rescale(templates[1], 0.5, anti_aliasing=False)
        #cv.imshow('s', rescaled)
        #cv.waitKey(0)

    #np.savetxt('wew.dat', img[templates[0][0]:templates[0][2],templates[0][1]:templates[0][3]], fmt='%d')

    #with open('./font-templates/times-new-roman-0.dat', 'w') as f:
    #    tnr0 = img[templates[0][0]:templates[0][2],templates[0][1]:templates[0][3]]
    #    f.write(str(tnr0))
    #with open('./font-templates/times-new-roman-5.dat', 'w') as f:
    #    tnr5 = img[templates[1][0]:templates[1][2],templates[1][1]:templates[1][3]]
    #with open('./font-templates/times-new-roman-1.dat', 'w') as f:
    #    tnr1 = img[templates[2][0]:templates[2][2],templates[2][1]:templates[2][3]]
    #with open('./font-templates/times-new-roman-6.dat', 'w') as f:
    #    tnr6 = img[templates[3][0]:templates[3][2],templates[3][1]:templates[3][3]]
    #with open('./font-templates/times-new-roman-2.dat', 'w') as f:
    #    tnr2 = img[templates[4][0]:templates[4][2],templates[4][1]:templates[4][3]]
    #with open('./font-templates/times-new-roman-7.dat', 'w') as f:
    #    tnr7 = img[templates[5][0]:templates[5][2],templates[5][1]:templates[5][3]]
    #with open('./font-templates/times-new-roman-3.dat', 'w') as f:
    #    tnr3 = img[templates[6][0]:templates[6][2],templates[6][1]:templates[6][3]]
    #with open('./font-templates/times-new-roman-8.dat', 'w') as f:
    #    tnr8 = img[templates[7][0]:templates[7][2],templates[7][1]:templates[7][3]]
    #with open('./font-templates/times-new-roman-4.dat', 'w') as f:
    #    tnr4 = img[templates[8][0]:templates[8][2],templates[8][1]:templates[8][3]]
    #with open('./font-templates/times-new-roman-9.dat', 'w') as f:
    #    tnr9 = img[templates[9][0]:templates[9][2],templates[9][1]:templates[9][3]]
    #with open('./font-templates/times-new-roman-L.dat', 'w') as f:
    #    tnrL = img[templates[10][0]:templates[10][2],templates[10][1]:templates[10][3]]
    #with open('./font-templates/times-new-roman-R.dat', 'w') as f:
    #    tnrR = img[templates[11][0]:templates[11][2],templates[11][1]:templates[11][3]]

    #plt.imshow(tnrL)
    #plt.show()

    #for (x1, y1, x2, y2) in templates:
    #    plt.imshow(img[x1:x2,y1:y2])
    #    plt.show()

main()
