// ģ��ƥ��ʾ��
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "path.h"
using namespace cv;

#define WINDOW_NAME1 "��ԭʼͼƬ��"        //Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_NAME2 "��ƥ�䴰�ڡ�"        //Ϊ���ڱ��ⶨ��ĺ� 

Mat g_srcImage; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching( int, void* );

int main()
{
	system("color 1F"); 

	g_srcImage = imread( MediaPath+"CH9/matchTemplate1.jpg", 1 );
	g_templateImage = imread( MediaPath+"CH9/matchTemplate2.jpg", 1 );

	namedWindow( WINDOW_NAME1, WINDOW_AUTOSIZE );
	namedWindow( WINDOW_NAME2, WINDOW_AUTOSIZE );

	createTrackbar( "����", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching );
	on_Matching( 0, 0 );

	waitKey(0);
	return 0;
}

void on_Matching( int, void* )
{
	Mat srcImage;
	g_srcImage.copyTo( srcImage );

	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	int resultImage_cols =  g_srcImage.cols - g_templateImage.cols + 1;
	g_resultImage.create(resultImage_rows,resultImage_cols, CV_32FC1);

	// ����ƥ��ͱ�׼��
	matchTemplate( g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod );
	normalize( g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat() );

	// ͨ������ minMaxLoc ��λ��ƥ���λ��
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	Point matchLocation;
	minMaxLoc( g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	// ���ڷ��� SQDIFF �� SQDIFF_NORMED, ԽС����ֵ���Ÿ��ߵ�ƥ����. ������ķ���, ��ֵԽ��ƥ��Ч��Խ��
	if( g_nMatchMethod  == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED )
	{ matchLocation = minLocation; }
	else
	{ matchLocation = maxLocation; }

	// ���Ƴ����Σ�����ʾ���ս��
	rectangle( srcImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );
	rectangle( g_resultImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );

	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, g_resultImage );
}


