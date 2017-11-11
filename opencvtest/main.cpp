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

cv::Mat getPicWith(cv::Mat originalMat); //获取图片
void showMatWith(cv::Mat originalMat, float framerate); //展示图片
void dealWithVedioAbout();


int main(int argc, char const *argv[])
{

	cout << "work oright" << endl;

    dealWithVedioAbout();



    // cv::Mat testPic = cv::imread("/Users/liangkun/Desktop/testPic.png"); //得到图片

    // cv::Mat pic = getPicWith(testPic);

    // showMatWith(pic, 0.5);


    // cout <<  testPic.rows << endl; //图片的高

    // cout << testPic.cols << endl; //图片的宽

    // cv::Rect rect(0,0,testPic.cols,testPic.rows / 2); 

    // cv::Rect rect1(0,testPic.rows / 2,testPic.cols, testPic.rows / 2);


    // cv::Mat image_cutTopHalf = cv::Mat(testPic, rect);  //从中间切割的图片

    // cv::Mat image_cutBottomHalf = cv::Mat(testPic, rect1);  //从中间切割的图片

    // cv::Mat hcombine,vcombine1;

    // cv::hconcat(image_cutTopHalf,image_cutBottomHalf,hcombine);    //水平方向的拼接

    // cv::namedWindow("topPic");  //显示的窗口

    // cv::namedWindow("bottomPic");

    //  // cv::imshow("topPic",image_cutTopHalf);
    //  cv::imshow("hcombine",hcombine);

    //  // 每一帧之间的延迟
    // int delay= 1000/0.5;

    // cv::waitKey(delay);

	return 0;
}

cv::Mat getPicWith(cv::Mat originalMat)
{

    cv::Rect rect(0,0,originalMat.cols,originalMat.rows / 2); 

    cv::Rect rect1(0,originalMat.rows / 2,originalMat.cols, originalMat.rows / 2);


    cv::Mat image_cutTopHalf = cv::Mat(originalMat, rect);  //从中间切割的图片

    cv::Mat image_cutBottomHalf = cv::Mat(originalMat, rect1);  //从中间切割的图片

    cv::Mat hcombine,vcombine1;

    cv::hconcat(image_cutTopHalf,image_cutBottomHalf,hcombine);    //水平方向的拼接

    // cv::hconcat(image_cutTopHalf,image_cutBottomHalf,hcombine);    //垂直方向的拼接
    // showMatWith(hcombine);

    return hcombine;

}

void showMatWith(cv::Mat originalMat, float framerate)
{
    cv::namedWindow("topPic");  //显示的窗口

     // 每一帧之间的延迟时间
    int delay= 1000/framerate;

    cv::imshow("topPic",originalMat); //显示

    cv::waitKey(delay); //等待

}

void dealWithVedioAbout()
{


    // 读取视频流
    cv::VideoCapture capture("file:///Users/liangkun/Desktop/Svr46.mp4");
    // 检测视频是否读取成功
    if (!capture.isOpened())
    {
        cout << "No Input Image";

    }

    // 获取图像帧率
    double rate= capture.get(CV_CAP_PROP_FPS);

    cout << rate <<endl;


    bool stop(false);

    cv::Mat frame; // 当前视频帧

    cv::namedWindow("Extracted Frame");

    // 每一帧之间的延迟
    // int delay= 1000/rate;
    int delay = 0;



    char *final_video_path = "file:///Users/liangkun/Desktop/Svr46final.avi"; //图片写入的URL
    int isColor = 1;    //是否是彩色的
    double fps = rate;  //美妙有多少个图

    CvSize size = cvSize(2160 * 2, 2160 / 2);

    cv::VideoWriter pWriter(final_video_path, CV_FOURCC('M', 'J', 'P', 'G'), fps, size, isColor);

    while(capture.read(frame))
    {
        cv::Mat image_final = getPicWith(frame);

        pWriter.write(image_final);

        cout << "write going" << endl;
    }
    pWriter.release();



    // // // 遍历每一帧
    // while (!stop)
    // {
    //     // 尝试读取下一帧
    //     if (!capture.read(frame))
    //     {
    //         break;
    //     }


    //     cout <<  "width of pic is" + frame.rows << endl;  //图片的高
    //     cout << " height of pic is" + frame.cols << endl;   //图片的宽


    //     cv::Rect rect(0,0,frame.cols,frame.rows / 2);   //创建一个Rect框，属于cv中的类，四个参数代表x,y,width,height  

    //     cv::Mat image_cut = cv::Mat(frame, rect); 


    //     cv::Mat image_final = getPicWith(frame);


    //     pWriter.write(image_final);

    //     //显示当前的图像
    //     cv::imshow("Extracted Frame",image_final);


    //     // 引入延迟
    //     if (cv::waitKey(delay) >= 0)
    //     {
    //          stop= true;
    //     }

    // }



}

