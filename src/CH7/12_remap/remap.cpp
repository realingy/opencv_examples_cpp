// remap函数用法示例
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "path.h"
using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	srcImage = imread(MediaPath+"1.jpg", 1);
	if(!srcImage.data ) { printf("读取图片错误！ \n"); return -1; }  

	imshow("原始图",srcImage);

	dstImage.create( srcImage.size(), srcImage.type() );
	map_x.create( srcImage.size(), CV_32FC1 );
	map_y.create( srcImage.size(), CV_32FC1 );

	// 遍历像素，改变map_x & map_y的值
	for( int j = 0; j < srcImage.rows;j++)
	{ 
		for( int i = 0; i < srcImage.cols;i++)
		{
			//改变map_x & map_y的值. 
			map_x.at<float>(j,i) = static_cast<float>(i);
			map_y.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
		} 
	}

	// 进行重映射操作
	remap( srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

	imshow( "【程序窗口】", dstImage );
	waitKey();

	return 0;
}

