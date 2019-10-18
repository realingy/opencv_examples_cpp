#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	std::string path = MediaPath + "1.jpg";
    Mat srcImage = imread(path);
	if (srcImage.data == nullptr) {
		cout << "tttttttttttttt\n";
	}
    imshow("src", srcImage); //显示
    waitKey(1000);

    Mat dstImage;
    blur(srcImage, dstImage, Size(8,8));
    imshow("blur", dstImage); //blur
    waitKey(0);

    return 0;
}
