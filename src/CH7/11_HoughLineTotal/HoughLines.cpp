// �����߱任�ۺ�ʾ��
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage,g_midImage; //ԭʼͼ���м�ͼ��Ч��ͼ
vector<Vec4i> g_lines; //����һ��ʸ���ṹg_lines���ڴ�ŵõ����߶�ʸ������
//�������յ�TrackBarλ�ò���
int g_nthreshold=100;

static void on_HoughLines(int, void*);//�ص�����

int main( )
{
	system("color 4F");  

	Mat g_srcImage = imread(MediaPath + "1.jpg");

	imshow("��ԭʼͼ��", g_srcImage);  

	namedWindow("��Ч��ͼ��",1);
	createTrackbar("ֵ", "��Ч��ͼ��",&g_nthreshold,200,on_HoughLines);

	// ���б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(g_srcImage, g_midImage, 50, 200, 3);//����һ��canny��Ե���
	cvtColor(g_midImage,g_dstImage, COLOR_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ

	// ����һ�λص�����������һ��HoughLinesP����
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10 );

	imshow("��Ч��ͼ��", g_dstImage);  

	waitKey(0);  

	return 0;  
}

//����ñ����/��ñ���㡿���ڵĻص�����
static void on_HoughLines(int, void*)
{
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//����HoughLinesP����
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/180, g_nthreshold+1, 50, 10 );

	//ѭ����������ÿһ���߶�
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, LINE_AA);
	}
	imshow("��Ч��ͼ��",dstImage);
}
