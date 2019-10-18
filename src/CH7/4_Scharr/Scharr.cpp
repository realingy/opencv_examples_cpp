#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	Mat src = imread(MediaPath + "apple.jpg");

	imshow("【原始图】Scharr滤波器", src);

	// 求X方向梯度
	Scharr( src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );
	imshow("【效果图】 X方向Scharr", abs_grad_x);

	// 求Y方向梯度
	Scharr( src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );
	imshow("【效果图】Y方向Scharr", abs_grad_y);

	// 合并梯度(近似)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);

	imshow("【效果图】合并梯度后Scharr", dst); 

	waitKey(0); 
	return 0; 
}