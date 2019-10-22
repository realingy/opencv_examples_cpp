#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread(MediaPath + "cbd.jpg");
	imshow("��ԭʼͼ��", srcImage);  

	Mat midImage,dstImage;

	Canny(srcImage, midImage, 50, 200, 3); //����һ��canny��Ե���
	cvtColor(midImage,dstImage, CV_GRAY2BGR); //ת����Ե�����ͼΪ�Ҷ�ͼ

	// ���л����߱任
	vector<Vec4i> lines; //����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10);

	// ������ͼ�л��Ƴ�ÿ���߶�
	for(size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, LINE_AA);
	}

	imshow("����Ե�����ͼ��", midImage);  
	imshow("��Ч��ͼ��", dstImage);  

	waitKey(0);

	return 0;
}


