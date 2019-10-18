#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main()
{
	Mat srcImage = imread(MediaPath + "kitty.jpg");
	if (!srcImage.data) { printf("open source image failed!");  return 0; }

	imshow("【原图】腐蚀操作", srcImage);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);

	imshow("【效果图】腐蚀操作", dstImage);
	waitKey(0); 

	return 0;
}