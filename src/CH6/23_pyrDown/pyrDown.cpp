#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main( )
{
	Mat srcImage = imread(MediaPath + "kid.jpg");
	Mat tmpImage, dstImage;//��ʱ������Ŀ��ͼ�Ķ���
	tmpImage = srcImage;//��ԭʼͼ������ʱ����

	imshow("��ԭʼͼ��", srcImage);

	pyrDown(tmpImage, dstImage, Size( tmpImage.cols/2, tmpImage.rows/2 ));

	imshow("��Ч��ͼ��", dstImage);

	waitKey(0);

	return 0;
}
