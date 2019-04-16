#include <Python.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <facedetectcnn.h>
using namespace cv;
#define DETECT_BUFFER_SIZE 0x20000


PyObject * facedetect_cnn(int rows, int cols, int n, unsigned char * img)
{
    int * pResults = NULL;
    unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);
    PyObject * result;

    printf("facedetect_cnn is called\n");
    printf("cols=%d, rows=%d, n=%d\n", cols, rows, n);
    // printf("----------- load array info--------------\n");
    Mat image = cv::Mat(rows, cols, 16, img);

    pResults = facedetect_cnn(pBuffer, (unsigned char*)(image.ptr(0)), image.cols, image.rows, (int)image.step);
    printf("%d faces detected.\n", (pResults ? *pResults : 0));

    if (pResults){
        int count = *pResults;
        result = PyList_New(count);
        for(int i = 0; i < count; i++)
        {
            short * p = ((short*)(pResults+1))+142*i;
            int x = p[0];
            int y = p[1];
            int w = p[2];
            int h = p[3];
            int confidence = p[4];
            int angle = p[5];
            //printf("face_rect=[%d, %d, %d, %d], confidence=%d, angle=%d\n", x,y,w,h,confidence, angle);
            printf("{'rect': [%d, %d, %d, %d], 'confidence': %d, 'angle':%d},\n", x,y,w,h,confidence, angle);
            PyObject * record = Py_BuildValue("{s:i,s:i,s:i,s:i,s:i,s:i}", "x", x, "y", y, "w", w, "h", h, "confidence", confidence, "angle", angle);
            PyList_SetItem(result, i, record);
        }
    }else{
        result = Py_BuildValue("[]");
    }

    return result;
}
