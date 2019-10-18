#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main()
{
	Mat srcImage = imread(MediaPath + "kid.jpg");
	if(!srcImage.data) {printf("read source image failed！\n"); return 0;}

	Mat tmpImage,dstImage1,dstImage2;//临时变量和目标图的定义
	tmpImage=srcImage;//将原始图赋给临时变量

	//显示原始图  
	imshow("【原始图】", srcImage);  

	//进行尺寸调整操作
	resize(tmpImage,dstImage1,Size( tmpImage.cols/2, tmpImage.rows/2 ),(0,0),(0,0),3);
	resize(tmpImage,dstImage2,Size( tmpImage.cols*2, tmpImage.rows*2 ),(0,0),(0,0),3);

	imshow("【效果图】之一", dstImage1);  
	imshow("【效果图】之二", dstImage2);  

	waitKey(0);  
	return 0;  
}
