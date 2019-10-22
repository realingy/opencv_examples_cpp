// ͼ���޲�ʾ��
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/photo.hpp"
#include <iostream>
#include "path.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME0 "��ԭʼͼ�ο���" //Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_NAME1 "��ԭʼͼ��" //Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_NAME2 "���޲����Ч��ͼ��" //Ϊ���ڱ��ⶨ��ĺ� 

Mat srcImage0,srcImage1, inpaintMask;
Point previousPoint(-1,-1); //ԭ���ĵ�����

static void On_Mouse( int event, int x, int y, int flags, void* )
{
	//������������Ϣ
	if( event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON) )
		previousPoint = Point(-1,-1);
	//������������Ϣ
	else if( event == EVENT_LBUTTONDOWN )
		previousPoint = Point(x,y);
	//��갴�²��ƶ������л���
	else if( event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON) )
	{
		Point pt(x,y);
		if( previousPoint.x < 0 )
			previousPoint = pt;
		//���ư�ɫ����
		line( inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
		line( srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcImage1);
	}
}

int main(int argc, char** argv)
{
	//����ԭʼͼ��������Ĥ�ĳ�ʼ��
	Mat srcImage = imread(MediaPath+"inpaint.jpg", -1);
	if(!srcImage.data)
	{
		printf("��ȡͼƬ����\n");
		return false;
	}

	srcImage0 = srcImage.clone();
	srcImage1 = srcImage.clone();
	inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);

	//��ʾԭʼͼ�ο�
	imshow(WINDOW_NAME0, srcImage0);
	//��ʾԭʼͼ
	imshow(WINDOW_NAME1, srcImage1);
	//�������ص���Ϣ
	setMouseCallback( WINDOW_NAME1, On_Mouse, 0 );

	//��ѯ���������ݲ�ͬ�İ������д���
	while (1)
	{
		//��ȡ������ֵ
		char c = (char)waitKey();

		//��ֵΪESC�������˳�
		if( c == 27 )
			break;

		//��ֵΪ2���ָ���ԭʼͼ��
		if( c == '2' )
		{
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(srcImage1);
			imshow(WINDOW_NAME1, srcImage1);
		}

		//��ֵΪ1���߿ո񣬽���ͼ���޲�����
		if( c == '1' || c == ' ' )
		{
			Mat inpaintedImage;
			inpaint(srcImage1, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}

	return 0;
}

