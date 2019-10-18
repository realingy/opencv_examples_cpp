//程序描述：用morphologyEx进行形态学顶帽运算
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"
using namespace cv;

int main()
{
	//载入原始图   
	Mat image = imread(MediaPath + "lemon.jpg");  //工程目录下应该有一张名为1.jpg的素材图
	if(!image.data) {printf("read source image failed！\n"); return 0;}

	//显示原始图  
	imshow("【原始图】顶帽运算", image);  
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	//进行形态学操作
	morphologyEx(image, image, MORPH_TOPHAT, element);
	//显示效果图  
	imshow("【效果图】顶帽运算", image);  

	waitKey(0);  

	return 0;  
}
