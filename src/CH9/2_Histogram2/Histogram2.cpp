// һάֱ��ͼ�Ļ���
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "path.h"
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread(MediaPath+"CH9/Histogram2.jpg", 0);
	imshow("ԭͼ",srcImage);
	if(!srcImage.data) {cout << "fail to load image" << endl; 	return 0;}

	system("color 1F");

	MatND dstHist;       // ��cv����CvHistogram *hist = cvCreateHist
	int dims = 1;
	float hranges[] = {0, 255};
	const float *ranges[] = {hranges};   // ������ҪΪconst����
	int size = 256;
	int channels = 0;

	// ����ͼ���ֱ��ͼ
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);    // cv ����cvCalcHist
	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
	// ��ȡ���ֵ����Сֵ
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist,&minValue, &maxValue, 0, 0);  //  ��cv���õ���cvGetMinMaxHistValue

	// ���Ƴ�ֱ��ͼ
	int hpt = saturate_cast<int>(0.9 * size);
	for(int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);           //   ע��hist����float����    ����OpenCV1.0������cvQueryHistValue_1D
		int realValue = saturate_cast<int>(binValue * hpt/maxValue);
		rectangle(dstImage,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(255));
	}

	imshow("һάֱ��ͼ", dstImage);
	waitKey(0);
	return 0;
}