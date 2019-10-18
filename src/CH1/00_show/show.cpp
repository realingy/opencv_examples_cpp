#include <opencv2/opencv.hpp>
#include "path.h"
using namespace cv;

int main()
{
	// ¶ÁÈëÍ¼Æ¬
	std::string path = MediaPath + "1.jpg";
    Mat img = imread(path);
    // ÏÔÊ¾Í¼Æ¬
	imshow("image",img);
	// ÑÓÊ±
	waitKey(6000);
}