#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main()
{
	Mat srcImage = imread(MediaPath + "kitty.jpg");
	if (!srcImage.data) { printf("open source image failed!");  return 0; }

	imshow("��ԭͼ����ʴ����", srcImage);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);

	imshow("��Ч��ͼ����ʴ����", dstImage);
	waitKey(0); 

	return 0;
}