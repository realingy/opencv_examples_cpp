#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main( )
{
	//载入原始图
	Mat srcImage = imread(MediaPath + "kid.jpg");
	if(!srcImage.data) {printf("read source image failed！\n"); return 0;}

	Mat tmpImage,dstImage;//临时变量和目标图的定义
	tmpImage=srcImage;//将原始图赋给临时变量

	//显示原始图  
	imshow("【原始图】", srcImage);  
	//进行向上取样操作
	pyrUp( tmpImage, dstImage, Size( tmpImage.cols*2, tmpImage.rows*2 ) );

	imshow("【效果图】", dstImage);  

	waitKey(0);  

	return 0;  
}
