#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    VideoCapture capture(0);

    while(1)
    {
        Mat frame; //定义frame存储视屏帧
        capture>>frame;  //读取当前帧
        imshow("video capture", frame);   //显示当前帧
        waitKey(30);    //延时
    }

    return 0;
}
