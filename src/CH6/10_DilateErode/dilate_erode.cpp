#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "path.h"

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;		//ԭʼͼ��Ч��ͼ
int g_nTrackbarNumer = 0;		//0��ʾ��ʴerode, 1��ʾ����dilate
int g_nStructElementSize = 3;	//�ṹԪ��(�ں˾���)�ĳߴ�

void Process();							//���ͺ͸�ʴ�Ĵ�����
void on_TrackbarNumChange(int, void *);	//�ص�����
void on_ElementSizeChange(int, void *);	//�ص�����

int main()
{
	system("color 2F");

	g_srcImage = imread(MediaPath + "cat.jpg");
	if( !g_srcImage.data ) { printf("read source image failed��\n"); return 0; }

	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��", g_srcImage);

	namedWindow("��Ч��ͼ��");
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));
	erode(g_srcImage, g_dstImage, element);
	imshow("��Ч��ͼ��", g_dstImage);

	createTrackbar("��ʴ/����", "��Ч��ͼ��", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�", "��Ч��ͼ��", &g_nStructElementSize, 21, on_ElementSizeChange);

	cout<<endl<<"\t���гɹ���������������۲�ͼ��Ч��~\n\n"
		<<"\t���¡�q����ʱ�������˳���\n";

	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//�����������Զ���ĸ�ʴ�����Ͳ���
void Process() 
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));

	if(g_nTrackbarNumer == 0) {    
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("��Ч��ͼ��", g_dstImage);
}

//��������ʴ������֮���л����صĻص�����
void on_TrackbarNumChange(int, void *) 
{
	//��ʴ������֮��Ч���Ѿ��л����ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}

//��������ʴ�����Ͳ����ں˸ı�ʱ�Ļص�����
void on_ElementSizeChange(int, void *)
{
	//�ں˳ߴ��Ѹı䣬�ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}

