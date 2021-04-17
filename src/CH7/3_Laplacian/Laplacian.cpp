#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

//二阶微分算子，目的是提供一幅用零交叉确定边缘位置的图像
int main()
{
	Mat src, src_gray, dst, abs_dst;

	//src = imread(MediaPath + "lady.jpg");
	src = imread(MediaPath + "girl2.jpg");

	imshow("【原始图】图像Laplace变换", src); 

	// 使用高斯滤波消除噪声
	GaussianBlur(src, src, Size(3,3), 0, 0, BORDER_DEFAULT);

	cvtColor(src, src_gray, CV_RGB2GRAY);

	// 使用Laplace函数
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	// 计算绝对值，并将结果转换成8位
	convertScaleAbs(dst, abs_dst);

	imshow("【效果图】图像Laplace变换", abs_dst);

	imwrite("laplace.jpg", abs_dst);

	waitKey(0); 

	return 0; 
}