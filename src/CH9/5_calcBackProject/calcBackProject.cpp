// ����ͶӰʾ������
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "path.h"
using namespace cv;

#define WINDOW_NAME1 "��ԭʼͼ��"        //Ϊ���ڱ��ⶨ��ĺ� 

Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//ֱ��ͼ���

void on_BinChange(int, void* );

int main( )
{
	system("color 6F"); 

	g_srcImage = imread( MediaPath+"CH9/calcBackProject.jpg", 1 );
	if(!g_srcImage.data ) { printf("��ȡͼƬ���� \n"); return -1; } 
	cvtColor( g_srcImage, g_hsvImage, COLOR_BGR2HSV );

	// ����Hueɫ��ͨ��
	g_hueImage.create( g_hsvImage.size(), g_hsvImage.depth() );
	int ch[ ] = { 0, 0 };
	mixChannels( &g_hsvImage, 1, &g_hueImage, 1, ch, 1 );

	// ���� Trackbar ������bin����Ŀ
	namedWindow( WINDOW_NAME1 , WINDOW_AUTOSIZE );
	createTrackbar("ɫ����� ", WINDOW_NAME1 , &g_bins, 180, on_BinChange );
	on_BinChange(0, 0);//����һ�γ�ʼ��

	imshow( WINDOW_NAME1 , g_srcImage );

	waitKey(0);
	return 0;
}

void on_BinChange(int, void* )
{
	MatND hist;
	int histSize = MAX( g_bins, 2 );
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	// ����ֱ��ͼ����һ��
	calcHist( &g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
	normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

	// ���㷴��ͶӰ
	MatND backproj;
	calcBackProject( &g_hueImage, 1, 0, hist, backproj, &ranges, 1, true );

	// ��ʾ����ͶӰ
	imshow( "����ͶӰͼ", backproj );

	// ����ֱ��ͼ�Ĳ���׼��
	int w = 400; int h = 400;
	int bin_w = cvRound( (double) w / histSize );
	Mat histImg = Mat::zeros( w, h, CV_8UC3 );

	// ����ֱ��ͼ
	for( int i = 0; i < g_bins; i ++ )
	{ rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 100, 123, 255 ), -1 ); }

	imshow( "ֱ��ͼ", histImg );
}


