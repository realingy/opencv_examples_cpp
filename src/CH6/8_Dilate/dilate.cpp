#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread(MediaPath + "puppy.jpg");
	if (!image.data) { printf("open source image failed!");  return 0; }

	imshow("��ԭͼ�����Ͳ���", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;
	dilate(image, out, element);

	imshow("��Ч��ͼ�����Ͳ���", out);

	waitKey(0); 

	return 0;
}