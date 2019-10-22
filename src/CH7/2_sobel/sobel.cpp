#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

//第一步、分别在x和y两个方向上求导
//第二步、检测水平方向上的边缘，内核为
//[-1  0 +1]
//[-2  0 +2]
//[-1  0 +1]
//第三步、检测垂直方向上的边缘，内核为
//[-1 -2 -1]
//[ 0  0  0]
//[+1 +2 +1]
//第四步、合并梯度

int main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,dst;

	Mat src = imread(MediaPath + "girl2.jpg");

	imshow("【原始图】sobel边缘检测", src); 

	// 求X方向梯度
	Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );
	imshow("【效果图】 X方向Sobel", abs_grad_x); 

	// 求Y方向梯度
	Sobel( src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );
	imshow("【效果图】Y方向Sobel", abs_grad_y); 

	// 合并梯度(近似)
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
	imshow("【效果图】整体方向Sobel", dst); 

	waitKey(0); 
	return 0; 
}



