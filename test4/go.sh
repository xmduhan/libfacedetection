#!/bin/bash

swig -c++ -python libfdt.i
gcc -c -fPIC libfdt.cpp libfdt_wrap.cxx -I/usr/include/python2.7/ -I/usr/local/lib/python2.7/dist-packages/numpy/core/include/ -I../src
g++ -shared libfdt.o libfdt_wrap.o ../build/libfacedetection.a -o _libfdt.so \
-I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_contrib -lopencv_stitching -lopencv_nonfree -lopencv_superres -lopencv_ocl -lopencv_ts -lopencv_videostab -lopencv_gpu -lopencv_photo -lopencv_objdetect -lopencv_legacy -lopencv_video -lopencv_ml -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_imgproc -lopencv_flann -lopencv_core -lQtCore -lQtTest -lQtGui -lQtOpenGL -lIlmThread -lHalf -lIex -lIlmImf -lImath -ljasper -ltiff -lpng -ljpeg -lswscale-ffmpeg -lavutil-ffmpeg -lavformat-ffmpeg -lavcodec-ffmpeg -lv4l2 -lv4l1 -ldc1394 -lgstpbutils-0.10 -lgstriff-0.10 -lgstapp-0.10 -lgstvideo-0.10 -lxml2 -lglib-2.0 -lgthread-2.0 -lgmodule-2.0 -lgobject-2.0 -lgstreamer-0.10 -lgstbase-0.10 -lGL -lGLU -lz -latomic -ltbb -lrt -lpthread -lm -ldl -lstdc++ \
-L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib -lpython2.7 -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions
python test.py
