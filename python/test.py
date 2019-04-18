#!/usr/bin/env python
# encoding: utf-8

import cv2
import libfdt

cap = cv2.VideoCapture(0)

mul = 4

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    cols, rows = frame.shape[:-1]
    small_frame = cv2.resize(frame, (int(rows / mul), int(cols / mul)))
    result_list = libfdt.facedetect_cnn(small_frame)
    for result in result_list:
        print(result)
        x0, y0 = result['x'], result['y']
        x1, y1 = x0 + result['w'], y0 + result['h']
        cv2.rectangle(frame, (x0 * mul, y0 * mul), (x1 * mul, y1 * mul), (255, 0, 0), 2)

    # Display the resulting frame
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
