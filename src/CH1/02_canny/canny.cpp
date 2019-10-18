#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
    // [0]读取原图
	std::string path = MediaPath + "1.jpg";
    Mat srcImage = imread(path);
    imshow("src", srcImage); 	//显示原始图

    Mat dstImage,edge,grayImage;	//参数定义

    // [1]创建与src同类型和大小的矩阵(dst)
    dstImage.create( srcImage.size(), srcImage.type() );

    // [2]将原图像转换为灰度图像
    //此句代码的OpenCV2版为：
    //cvtColor( srcImage, grayImage, CV_BGR2GRAY );
    //此句代码的OpenCV3版为：
    cvtColor( srcImage, grayImage, COLOR_BGR2GRAY ); //转换成灰度图

    // [3]先用使用3x3内核来降噪
    blur( grayImage, edge, Size(3,3) );

    // [4]运行Canny算子
    Canny( edge, edge, 3, 9, 3 );

    // [5]显示效果图
    imshow("canny", edge);

    waitKey(10000);

    return 0;
}
