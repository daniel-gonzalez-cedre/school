# PYTHON SCRIPT TO EXTRACT FRAMES FROM A VIDEO USING OpenCV
import os
import cv2 as cv

POS_FRAMES = 1
FRAME_RATE = 5
FRAME_COUNT = 7

def main():
    date = '2019-08-07'
    subject = '001'
    #r_dir = '/Users/akira/academia/research/WVU-CFC/data-collection/' + date + '/' + subject + '/'
    r_dir = '/Users/akira/academia/curriculum/nd/computer-vision/semester-project/'
    w_dir = './data/'
    v_name = 'movie.mov'
    video = cv.VideoCapture(r_dir + v_name)
    success, image = video.read()

    if success and not os.path.exists('./data'):
        os.makedirs(w_dir)

    try:
        print('\nTotal number of frames: ' + str(video.get(FRAME_COUNT))[:-2])
        skip = int(input('How many frames do you want to skip? '))
        while success:
            count = str(int(video.get(POS_FRAMES) - 1) + 1)
            print('frame:\t', count)
            while len(count) < 3:
                count = '0' + count
            image = cv.flip(cv.transpose(image), flipCode=1)
            cv.imwrite(w_dir + 'frame' + count + '.png', image)
            for i in range(0, skip + 1):
                success, image = video.read()
    except TypeError:
        print('The number of frames must be an integer.')
    except KeyboardInterrupt:
        print()

main()
