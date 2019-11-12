# PYTHON SCRIPT TO SEGMENT VIDEO FRAMES BASED ON INTENSITY
from skimage import measure
import os
import warnings
import cv2 as cv
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
sns.set(style='ticks', palette='Set2')

def h_tile(imgs, interpolation=cv.INTER_CUBIC):
    h_min = min(img.shape[0] for img in imgs)
    #print(imgs[0].shape)
    imgs = [cv.resize(img, (img.shape[1]*h_min//img.shape[0], h_min), interpolation=interpolation) for img in imgs]
    return cv.hconcat(imgs)

def main():
    # READ IMAGE IN GRAYSCALE
    for font in ['helvetica', 'times-new-roman']:
        img = cv.imread('./font-templates/' + font + '.png', 0)
        img = 255*np.ones(img.shape) - img
        rows, cols = img.shape

        img[img < 50] = 0
        img[img >= 50] = 255

        labels = measure.label(img, 8)
        features = measure.regionprops(labels)

        if font == 'times-new-roman':
            reverse = True
        else:
            reverse = False

        templates = list(map(lambda x: cv.flip(x, -1) if reverse else x, [f.image.astype(np.uint8) for f in features]))

        T = {}
        T['0'] = templates[0]
        T['1'] = templates[2]
        T['2'] = templates[4]
        T['3'] = templates[6]
        T['4'] = templates[8]
        T['5'] = templates[1]
        T['6'] = templates[3]
        T['7'] = templates[5]
        T['8'] = templates[7]
        T['9'] = templates[9]
        T['L'] = templates[10]
        T['R'] = templates[11]
        T['001'] = h_tile([T['0'], T['0'], T['1']][::-1 if reverse else 1])
        T['002'] = h_tile([T['0'], T['0'], T['2']][::-1 if reverse else 1])
        T['003'] = h_tile([T['0'], T['0'], T['3']][::-1 if reverse else 1])
        T['004'] = h_tile([T['0'], T['0'], T['4']][::-1 if reverse else 1])
        T['005'] = h_tile([T['0'], T['0'], T['5']][::-1 if reverse else 1])
        T['006'] = h_tile([T['0'], T['0'], T['6']][::-1 if reverse else 1])
        T['007'] = h_tile([T['0'], T['0'], T['7']][::-1 if reverse else 1])
        T['008'] = h_tile([T['0'], T['0'], T['8']][::-1 if reverse else 1])
        T['009'] = h_tile([T['0'], T['0'], T['9']][::-1 if reverse else 1])
        T['010'] = h_tile([T['0'], T['1'], T['0']][::-1 if reverse else 1])
        T['011'] = h_tile([T['0'], T['1'], T['1']][::-1 if reverse else 1])
        T['012'] = h_tile([T['0'], T['1'], T['2']][::-1 if reverse else 1])
        T['013'] = h_tile([T['0'], T['1'], T['3']][::-1 if reverse else 1])
        T['014'] = h_tile([T['0'], T['1'], T['4']][::-1 if reverse else 1])
        T['015'] = h_tile([T['0'], T['1'], T['5']][::-1 if reverse else 1])
        T['016'] = h_tile([T['0'], T['1'], T['6']][::-1 if reverse else 1])
        T['017'] = h_tile([T['0'], T['1'], T['7']][::-1 if reverse else 1])
        T['018'] = h_tile([T['0'], T['1'], T['8']][::-1 if reverse else 1])
        T['019'] = h_tile([T['0'], T['1'], T['9']][::-1 if reverse else 1])
        T['020'] = h_tile([T['0'], T['2'], T['0']][::-1 if reverse else 1])
        T['021'] = h_tile([T['0'], T['2'], T['1']][::-1 if reverse else 1])
        T['022'] = h_tile([T['0'], T['2'], T['2']][::-1 if reverse else 1])
        T['023'] = h_tile([T['0'], T['2'], T['3']][::-1 if reverse else 1])
        T['024'] = h_tile([T['0'], T['2'], T['4']][::-1 if reverse else 1])
        T['025'] = h_tile([T['0'], T['2'], T['5']][::-1 if reverse else 1])
        T['L1'] = h_tile([T['L'], T['1']])
        T['L2'] = h_tile([T['L'], T['2']])
        T['L3'] = h_tile([T['L'], T['3']])
        T['L4'] = h_tile([T['L'], T['4']])
        T['L5'] = h_tile([T['L'], T['5']])
        T['R1'] = h_tile([T['R'], T['1']])
        T['R2'] = h_tile([T['R'], T['2']])
        T['R3'] = h_tile([T['R'], T['3']])
        T['R4'] = h_tile([T['R'], T['4']])
        T['R5'] = h_tile([T['R'], T['5']])

        #cv.imshow('wew', 255*templates[4])
        #cv.waitKey(0)
        #cv.imshow('wow', cv.flip(255*templates[4], -1))
        #cv.waitKey(0)
        #exit()

        for key in T.keys():
            filename = './font-templates/' + font + '-' + str(key) + '.npy'
            np.save(filename, T[key])

        #np.save('./font-templates/' + font + '-002.npy', h_tile([T[4], T[0], T[0]]))
            #cv.imshow('wew', 255*h_tile([T[4], T[0], T[0]]))
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-0.npy', T[0])
            #cv.imshow('wew', 255*T[0])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-1.npy', T[2])
            #cv.imshow('wew', 255*T[2])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-2.npy', T[4])
            #cv.imshow('wew', 255*T[4])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-3.npy', T[6])
            #cv.imshow('wew', 255*T[6])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-4.npy', T[8])
            #cv.imshow('wew', 255*T[8])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-5.npy', T[1])
            #cv.imshow('wew', 255*T[1])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-6.npy', T[3])
            #cv.imshow('wew', 255*T[3])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-7.npy', T[5])
            #cv.imshow('wew', 255*T[5])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-8.npy', T[7])
            #cv.imshow('wew', 255*T[7])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-9.npy', T[9])
            #cv.imshow('wew', 255*T[9])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-L.npy', T[10])
            #cv.imshow('wew', 255*T[10])
            #cv.waitKey(0)
            #np.save('./font-templates/' + font + '-R.npy', T[11])
            #cv.imshow('wew', 255*T[11])
            #cv.waitKey(0)

with warnings.catch_warnings():
    warnings.simplefilter('ignore')
    main()
