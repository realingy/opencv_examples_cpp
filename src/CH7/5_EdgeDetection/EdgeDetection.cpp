//��Ե����ۺ�ʾ������Canny����,Sobel����,Laplace����,Scharr�˲���
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

Mat g_srcImage, g_srcGrayImage, g_dstImage;

//Canny��Ե�����ر���
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold=1; //TrackBarλ�ò���  

//Sobel��Ե�����ر���
Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize=1;//TrackBarλ�ò���  

//Scharr�˲�����ر���
Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;

static void on_Canny(int, void*); //Canny��Ե��ⴰ�ڹ������Ļص�����
static void on_Sobel(int, void*); //Sobel��Ե��ⴰ�ڹ������Ļص�����
void Scharr( ); //��װ��Scharr��Ե�����ش���ĺ���

int main( int argc, char** argv )
{
	g_srcImage = imread(MediaPath + "girllake.jpg");
	if( !g_srcImage.data ) { printf("��ȡsrcImage����~�� \n"); return -1; }

	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��", g_srcImage);

	// ������srcͬ���ͺʹ�С�ľ���(dst)
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	// ��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor( g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY );

	namedWindow( "��Ч��ͼ��Canny��Ե���", WINDOW_AUTOSIZE );
	namedWindow( "��Ч��ͼ��Sobel��Ե���", WINDOW_AUTOSIZE );

	createTrackbar( "����ֵ��", "��Ч��ͼ��Canny��Ե���", &g_cannyLowThreshold, 120, on_Canny );
	createTrackbar( "����ֵ��", "��Ч��ͼ��Sobel��Ե���", &g_sobelKernelSize, 3, on_Sobel );

	on_Canny(0, 0);
	on_Sobel(0, 0);

	Scharr( );

	while((char(waitKey(1)) != 'q')) {}

	return 0;
}

void on_Canny(int, void*)
{
	// ��ʹ�� 3x3�ں�������
	blur( g_srcGrayImage, g_cannyDetectedEdges, Size(3,3) );

	// �������ǵ�Canny����
	Canny( g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*3, 3 );

	//�Ƚ�g_dstImage�ڵ�����Ԫ������Ϊ0 
	g_dstImage = Scalar::all(0);

	//ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��
	g_srcImage.copyTo( g_dstImage, g_cannyDetectedEdges);

	imshow( "��Ч��ͼ��Canny��Ե���", g_dstImage );
}

// Sobel��Ե��ⴰ�ڹ������Ļص�����
void on_Sobel(int, void*)
{
	// �� X�����ݶ�
	Sobel( g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_X, g_sobelAbsGradient_X );//�������ֵ���������ת����8λ

	// ��Y�����ݶ�
	Sobel( g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//�������ֵ���������ת����8λ

	// �ϲ��ݶ�
	addWeighted( g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage );

	imshow("��Ч��ͼ��Sobel��Ե���", g_dstImage); 

}

// ��װ��Scharr��Ե�����ش���ĺ���
void Scharr( )
{
	// ��X�����ݶ�
	Scharr( g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_X, g_scharrAbsGradient_X );//�������ֵ���������ת����8λ

	// ��Y�����ݶ�
	Scharr( g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_Y, g_scharrAbsGradient_Y );//�������ֵ���������ת����8λ

	// �ϲ��ݶ�
	addWeighted( g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage );

	imshow("��Ч��ͼ��Scharr�˲���", g_dstImage); 
}
