#include <opencv2/opencv.hpp>
#include "path.h"
using namespace cv;

int main()
{
	// ����ͼƬ
	std::string path = MediaPath + "1.jpg";
    Mat img = imread(path);
    // ��ʾͼƬ
	imshow("image",img);
	// ��ʱ
	waitKey(6000);
}