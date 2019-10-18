#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
    // 载入原始图
	std::string path = MediaPath + "11.jpg";
    Mat srcImage = imread(path);
    Mat dstImage1,dstImage2;

    // 显示原始图
    imshow("src", srcImage);

    // 进行尺寸调整操作
    resize(srcImage,dstImage1,Size( srcImage.cols/2, srcImage.rows/2 ),(0,0),(0,0),3);
    resize(srcImage,dstImage2,Size( srcImage.cols*2, srcImage.rows*2 ),(0,0),(0,0),3);

    // 显示效果图
    imshow("resuce", dstImage1);
    imshow("magnify", dstImage2);

    waitKey(0);
    return 0;
}
