#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <facedetectcnn.h>
using namespace cv;
#define DETECT_BUFFER_SIZE 0x20000

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


const char * facedetect_cnn(int rows, int cols, int n, unsigned char * img)
{
    int * pResults = NULL;
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    char buf[1024] = {0};
    static string * result = NULL;

    if (result) {
        free(result);
        result = NULL;
    }

    printf("_facedetect_cnn is called\n");
    printf("cols=%d, rows=%d, n=%d\n", cols, rows, n);
    printf("----------- load array info--------------\n");
    Mat image0 = cv::Mat(rows, cols, 16, img);
    string ty0 =  type2str( image0.type() );
    printf("Matrix: %s %dx%d \n", ty0.c_str(), image0.cols, image0.rows );

    pResults = facedetect_cnn(pBuffer, (unsigned char*)(image0.ptr(0)), image0.cols, image0.rows, (int)image0.step);
    printf("%d faces detected.\n", (pResults ? *pResults : 0));
    Mat result_cnn0 = image0.clone();
    //print the detection results
    for(int i = 0; i < (pResults ? *pResults : 0); i++)
    {
        short * p = ((short*)(pResults+1))+142*i;
        int x = p[0];
        int y = p[1];
        int w = p[2];
        int h = p[3];
        int confidence = p[4];
        int angle = p[5];

        printf("face_rect=[%d, %d, %d, %d], confidence=%d, angle=%d\n", x,y,w,h,confidence, angle);
        sprintf(buf, "%s{'rect': [%d, %d, %d, %d], 'confidence': %d, 'angle':%d},\n", buf, x,y,w,h,confidence, angle);
    }

    // printf("----------- load image info--------------\n");
    // // Mat image1 = imread("/home/duhan/notebook/libfacedetection/images/keliamoniz1.jpg");
    // Mat image1 = imread("/tmp/1.jpg");
    // string ty1 =  type2str(image1.type());
    // printf("Matrix: %s %dx%d \n", ty1.c_str(), image1.cols, image1.rows );

    // pResults = facedetect_cnn(pBuffer, (unsigned char*)(image1.ptr(0)), image1.cols, image1.rows, (int)image1.step);
    // printf("%d faces detected.\n", (pResults ? *pResults : 0));
    // Mat result_cnn1 = image1.clone();
    // //print the detection results
    // for(int i = 0; i < (pResults ? *pResults : 0); i++)
    // {
    //     short * p = ((short*)(pResults+1))+142*i;
    //     int x = p[0];
    //     int y = p[1];
    //     int w = p[2];
    //     int h = p[3];
    //     int confidence = p[4];
    //     int angle = p[5];

    //     printf("face_rect=[%d, %d, %d, %d], confidence=%d, angle=%d\n", x,y,w,h,confidence, angle);
    //     sprintf(buf, "%s{'rect': [%d, %d, %d, %d], 'confidence': %d, 'angle':%d},\n", buf, x,y,w,h,confidence, angle);
    //     printf(buf);
    // }

    // sprintf(buf, "[\n%s]", string(buf).c_str());
    // printf("--------------------------\n");
    // printf("finish!\n");

    result = new string(buf);
    return (*result).c_str();
}
