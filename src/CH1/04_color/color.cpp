#include <opencv2/opencv.hpp>
#include "path.h"

using namespace cv;

int main(void)
{
	std::string path = MediaPath + "1.jpg";
    Mat srcImage = imread(path);
    imshow("src", srcImage);

    Mat dstImage;
    cvtColor(srcImage, dstImage, 10);

    imshow("dst", dstImage);
    waitKey(10000);

	return 0;
}
