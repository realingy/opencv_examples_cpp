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

	imshow("【原图】膨胀操作", image);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;
	dilate(image, out, element);

	imshow("【效果图】膨胀操作", out);

	waitKey(0); 

	return 0;
}