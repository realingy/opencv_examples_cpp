#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main( )
{
	Mat image = imread( MediaPath + "lemon.jpg");
	if( !image.data ) { printf("read source image failed！\n"); return 0; }

	imshow("【原始图】膨胀", image);  
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	morphologyEx(image, image, MORPH_DILATE, element);
	imshow("【效果图】膨胀", image);  

	waitKey(0);  

	return 0;  
}
