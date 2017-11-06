//---------
//main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <assert.h>
// #include <math.h>
// #include <float.h>
// #include <limits.h>
// #include <time.h>
// #include <ctype.h>
#include <iostream>
// #include <string>

#include <cv.h>  
#include <highgui.h>  
#include <cxcore.h>  
#include <types_c.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::cout;
using std::endl;


void testSqlAbout();


int main(int argc, char const *argv[])
{

	cout << "work oright" << endl;

//用来保存图像捕获所需要的信息
// CvCapture *capture;

//结构体类型，用来保存一帧图像的信息，也就是一帧图像所有像素构成的一个矩阵
// IplImage *frame, *frame_copy = 0;

//如果初始化失败，那个capture为空指针 
// capture = cvCaptureFromFile("file:///Users/liangkun/Desktop/IMG_2224.MOV");

// if (capture)
// {
//    cout << "capture ok" << endl;
// }


// 读取视频流
    cv::VideoCapture capture("file:///Users/liangkun/Desktop/IMG_2224.MOV");
    // 检测视频是否读取成功
    if (!capture.isOpened())
    {
        cout << "No Input Image";
        return 1;
    }

    // 获取图像帧率
    double rate= capture.get(CV_CAP_PROP_FPS);
    bool stop(false);
    cv::Mat frame; // 当前视频帧
    cv::namedWindow("Extracted Frame");

    // 每一帧之间的延迟
    int delay= 1000/rate;

    // 遍历每一帧
    while (!stop)
    {
        // 尝试读取下一帧
        if (!capture.read(frame))
        {
            break;
        }
        cv::imshow("Extracted Frame",frame);

        // 引入延迟
        if (cv::waitKey(delay)>=0)
        {
        	 stop= true;
        }

               
    }



	return 0;
}

