#include <opencv2/opencv.hpp>
#include "path.h"

using namespace cv;

int main()
{
    std::string name = MediaPath + "1.avi";
//    const char *name = "D:\\project_opencv\\_media\\1.avi";
    VideoCapture capture;
    capture.open(name);
    if(!capture.isOpened())
        std::cout << "video can't opened!" << name << std::endl;

    while(1)
    {
        Mat frame; //定义frame存储视屏帧
        capture>>frame;  //读取当前帧
        if(frame.empty())
            break;
        imshow("video capture", frame);   //显示当前帧
        waitKey(30);    //延时

//        Mat image;
//        resize(frame, image, Size(frame.cols/2, frame.rows/2), INTER_LINEAR);
//        Mat ground;
//        if(ground.empty())
//            ground.create(image.size, image.type());

    }

    return 0;
}
