// �����������ҡ�findContours+drawContours
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "path.h"
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	Mat srcImage=imread(MediaPath+"findContours.jpg", 0);
	imshow("ԭʼͼ",srcImage);

	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	srcImage = srcImage > 119;
	imshow( "ȡ��ֵ���ԭʼͼ", srcImage );

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// ��������
	findContours( srcImage, contours, hierarchy,RETR_CCOMP, CHAIN_APPROX_SIMPLE );

	// �������ж���������� �������ɫ���Ƴ�ÿ�����������ɫ
	int index = 0;
	for( ; index >= 0; index = hierarchy[index][0] )
	{
		Scalar color( rand()&255, rand()&255, rand()&255 );
		drawContours( dstImage, contours, index, color, FILLED, 8, hierarchy );
	}

	imshow( "����ͼ", dstImage );

	waitKey(0);
	return 0;
}