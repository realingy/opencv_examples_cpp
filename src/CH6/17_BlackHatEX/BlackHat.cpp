#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main()
{
	//载入原始图
	Mat image = imread(MediaPath + "lemon.jpg");
	if(!image.data) {printf("read source image failed！\n"); return 0;}

	//显示原始图  
	imshow("【原始图】黑帽运算", image);  
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	//进行形态学操作
	morphologyEx(image, image, MORPH_BLACKHAT, element);

	imshow("【效果图】黑帽运算", image);  

	waitKey(0);  

	return 0;  
}
