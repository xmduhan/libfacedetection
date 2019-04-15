#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void facedetect_cnn(int rows, int cols, int n, unsigned char * img)
{
    printf("_facedetect_cnn is called\n");
    printf("cols=%d, rows=%d, n=%d\n", cols, rows, n);
    printf("----------- array info--------------\n");
    Mat m = cv::Mat(rows, cols, 16, img);
    string t1 =  type2str( m.type() );
    printf("Matrix: %s %dx%d \n", t1.c_str(), m.cols, m.rows );
    printf("----------- load image info--------------\n");
    Mat M = imread("/home/duhan/notebook/libfacedetection/images/keliamoniz1.jpg");
    string ty =  type2str( M.type() );
    printf("Matrix: %s %dx%d \n", ty.c_str(), M.cols, M.rows );
    printf("--------------------------\n");
    printf("finish!\n");
}
