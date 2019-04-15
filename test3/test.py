#!/usr/bin/env python
# encoding: utf-8
import cv2

import libfdt
img = cv2.imread('/home/duhan/notebook/libfacedetection/images/keliamoniz1.jpg')
# img = cv2.imread('/tmp/1.jpg')
print libfdt.facedetect_cnn(img)
print libfdt.facedetect_cnn(img)
# print libfdt.facedetect_cnn(img)
# print libfdt.facedetect_cnn(img)
