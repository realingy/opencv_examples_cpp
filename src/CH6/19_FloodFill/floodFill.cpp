#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include "path.h"
using namespace cv;  

int main()
{
	Mat src = imread(MediaPath + "roof.jpg"); 
	if(!src.data) {printf("read source image failed！\n"); return 0;}

	imshow("【原始图】",src);
	Rect ccomp;
	floodFill(src, Point(50,300), Scalar(155, 255,55), &ccomp, Scalar(20, 20, 20),Scalar(20, 20, 20));

	imshow("【效果图】",src);

	waitKey(0);
	return 0;    
}  