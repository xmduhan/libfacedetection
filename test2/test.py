#!/usr/bin/env python
# encoding: utf-8
import cv2

import libfdt
img = cv2.imread('/home/duhan/notebook/libfacedetection/images/keliamoniz1.jpg')
libfdt.facedetect_cnn(img)
