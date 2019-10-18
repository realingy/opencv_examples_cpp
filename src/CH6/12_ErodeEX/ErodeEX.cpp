#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
	Mat image = imread(MediaPath + "lemon.jpg");
	if( !image.data ) { printf("read source image failed！\n"); return 0; }

	imshow("【原始图】腐蚀", image);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	//进行形态学操作
	morphologyEx(image, image, MORPH_ERODE, element);

	imshow("【效果图】腐蚀", image);  

	waitKey(0);  

	return 0;  
}
