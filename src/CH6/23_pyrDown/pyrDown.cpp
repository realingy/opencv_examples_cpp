#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main( )
{
	Mat srcImage = imread(MediaPath + "kid.jpg");
	Mat tmpImage, dstImage;//临时变量和目标图的定义
	tmpImage = srcImage;//将原始图赋给临时变量

	imshow("【原始图】", srcImage);

	pyrDown(tmpImage, dstImage, Size( tmpImage.cols/2, tmpImage.rows/2 ));

	imshow("【效果图】", dstImage);

	waitKey(0);

	return 0;
}
