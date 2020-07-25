# Computer Vision Course (CSE 40535/60535)
# University of Notre Dame, Fall 2019
# ----------------------------------------------------------------
# Adam Czajka, Andrey Kuehlkamp, September 2017-2019

# Below are your tasks for today. Present your solutions to the instructor / TA in class.
# If you need more time, finish your codes at home and upload them to your SAKAI Dropbox by Wednesday, Sept. 18, 11:59 pm.
#
# Task 1 (2 points):
# - Select one candy that you want to track and set the RGB
#   channels to the selected ranges (using hsvSelection.py).
# - Check if HSV color space works better. Can you ignore one or two
#   channels when working in HSV color space ("ignore" = set the lower bound to 0 and upper bound to 255)? Is so, why?
# - Try to track candies of different colors (blue, yellow, green).
# - What happens when you put two candies of the same color into a video frame?
# - If you have not presented your solution to the instructor in class, upload your code solving this task to your SAKAI Dropbox as colorTracking1.py
#
# Task 2 (1 point):
# - Adapt your code to track multiple candies of *the same* color simultaneously.
# - Upload your solution to your SAKAI Dropbox as colorTracking2.py
#
# Task 3 (2 points):
# - Adapt your code to track multiple candies of *different* colors simultaneously.
# - Upload your solution to your SAKAI Dropbox as colorTracking3.py

import cv2
import numpy as np

cam = cv2.VideoCapture(0)

while (True):
    retval, img = cam.read()

    # rescale the input image if it's too large
    res_scale = 0.5
    img = cv2.resize(img, (0,0), fx = res_scale, fy = res_scale)

    #######################################################
    # TASK 1:
    # objmask = cv2.inRange(img, lower, upper)
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # RED
    red_lower = np.array([168, 180, 100])
    red_upper = np.array([178, 235, 150])

    # GREEN
    green_lower = np.array([66, 150, 50])
    green_upper = np.array([79, 255, 150])

    # YELLOW
    yellow_lower = np.array([15, 175, 130])
    yellow_upper = np.array([30, 255, 255])

    # BLUE
    blue_lower = np.array([103, 180, 100])
    blue_upper = np.array([115, 250, 170])

    lower = [green_lower, yellow_lower, blue_lower]
    upper = [green_upper, yellow_upper, blue_upper]

    objmask = sum(cv2.inRange(hsv, l, u) for l in lower for u in upper)

    #######################################################
    # you may use this for debugging
    cv2.imshow("Binary image", objmask)

    # Resulting binary image may have large number of small objects.
    # We can use morphological operations to remove these unnecessary elements:
    kernel = np.ones((5,5), np.uint8)
    objmask = cv2.morphologyEx(objmask, cv2.MORPH_CLOSE, kernel=kernel)
    objmask = cv2.morphologyEx(objmask, cv2.MORPH_DILATE, kernel=kernel)
    cv2.imshow("Image after morphological operations", objmask)

    # find connected components
    cc = cv2.connectedComponents(objmask)
    ccimg = cc[1].astype(np.uint8)

    # find contours of these objects:
    # use this if you have OpenCV 4.x version:
    contours, hierarchy = cv2.findContours(ccimg, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # use this if you have OpenCV 3.x version:
    # ret, contours, hierarchy = cv2.findContours(ccimg, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # You may display the countour points if you want:
    # cv2.drawContours(img, contours, -1, (255,0,0), 3)
    # ignore bounding boxes smaller than "minObjectSize"
    minObjectSize = 20;

    def func(args):
        x, y, w, h = args
        return w*h

    #######################################################
    # TASK 2:
    if contours:
        contour = max(contours, key=lambda c: func(cv2.boundingRect(c)))
        x, y, w, h = cv2.boundingRect(contour)

        #######################################################
        # TASK 2 tip: you want to get bounding boxes
        # of ALL contours (not only the first one)
        #######################################################
        # do not show very small objects
        if w > minObjectSize or h > minObjectSize:
            cv2.rectangle(img, (x, y), (x+w, y+h), (0,255,0), 3)
            cv2.putText(img,                        # image
                        "Here's my candy!",         # text
                        (x, y-10),                  # start position
                        cv2.FONT_HERSHEY_SIMPLEX,   # font
                        0.7,                        # size
                        (0, 255, 0),                # BGR color
                        1,                          # thickness
                        cv2.LINE_AA)                # type of line

            cv2.imshow("Live WebCam", img)
        #for contour in contours:
        #    x, y, w, h = cv2.boundingRect(contour)
        #    print(x, y, w, h)
        #    size = (w)*(h)
        #    exit()

        #    #######################################################
        #    # TASK 2 tip: you want to get bounding boxes
        #    # of ALL contours (not only the first one)
        #    #######################################################
        #    # do not show very small objects
        #    if w > minObjectSize or h > minObjectSize:
        #        cv2.rectangle(img, (x, y), (x+w, y+h), (0,255,0), 3)
        #        cv2.putText(img,                        # image
        #                    "Here's my candy!",         # text
        #                    (x, y-10),                  # start position
        #                    cv2.FONT_HERSHEY_SIMPLEX,   # font
        #                    0.7,                        # size
        #                    (0, 255, 0),                # BGR color
        #                    1,                          # thickness
        #                    cv2.LINE_AA)                # type of line

        #        cv2.imshow("Live WebCam", img)
    action = cv2.waitKey(1)
    if action == 27:
        break
