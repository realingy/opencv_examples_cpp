#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
	std::string name = MediaPath + "1.jpg";
    Mat srcImage = imread(name);
    imshow("rsc", srcImage);
    waitKey(1000);

    Mat dstImage;
    GaussianBlur(srcImage, dstImage, Size(7,7), 1000);

    imshow("gaussblur", dstImage);
    waitKey(0);

    return 0;
}
