#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;
using namespace std;

//�����߱任�����߼��
/********************************************************************************************
void HoughLines(InputArray image, //����ͼ��8λ��ͨ���Ķ�ֵͼ������ͼ����ܱ������޸ġ�
	OutputArray lines, //ֱ�ߵ����������ÿһ��ֱ��������Ԫ�ص�������rho,theta����ʾ
	double rho, double theta, //ֱ������ʱ�Ĳ����ߴ�
	int threshold, //��СͶƱ��
	double srn = 0, double stn = 0, //Ĭ��
	double min_theta = 0, double max_theta = CV_PI); //Ĭ��
********************************************************************************************/

int main()
{
	Mat srcImage = imread(MediaPath + "cbd.jpg");
	imshow("��ԭʼͼ��", srcImage);  

	Mat midImage, dstImage;

	Canny(srcImage, midImage, 50, 200, 3); //����һ��canny��Ե���
	cvtColor(midImage, dstImage, CV_GRAY2BGR); //ת����Ե�����ͼΪ�Ҷ�ͼ

	// ���л����߱任
	vector<Vec2f> lines; //����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLines(midImage, lines, 1, CV_PI/180, 150, 0, 0);

	// ������ͼ�л��Ƴ�ÿ���߶�
	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( dstImage, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
	}

	imshow("����Ե�����ͼ��", midImage);  

	imshow("��Ч��ͼ��", dstImage);  

	waitKey(0);

	return 0;  
}

