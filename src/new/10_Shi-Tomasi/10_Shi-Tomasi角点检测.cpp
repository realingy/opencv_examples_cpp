#include <opencv2/opencv.hpp>
#include <iostream>
#include "path.h"

using namespace cv;
using namespace std;

// ����ȫ�ֱ���
int num_corners = 25;
int max_corners = 200;
const string output_title = "Shi-Tomasi���";
void ShiTomasi_Demo(int, void*);                  // �ص���������
Mat src_img, gray_img;

//����һ��RNG����󣬱��ں���ʹ��rng.uniform(0, 255)������һ��0-255֮��
//���������������ֵ������ֵ�����������򷵻ص������Ҳ��������
RNG rng;

// ������
int main()
{
	src_img = imread(MediaPath + "1.jpg");
	if (src_img.empty())
	{
		printf("could not load the image...\n");
		return -1;
	}
	namedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	imshow("ԭͼ", src_img);
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);          //��ɫͼ��ת��Ϊ�Ҷ�ͼ��
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	createTrackbar("�ǵ���Ŀ", output_title, &num_corners, max_corners, ShiTomasi_Demo);     //����TrackBar
	ShiTomasi_Demo(0, 0);
	for (int i = 0; i < 20; ++i)
		cout << rng.uniform(0, 255) << endl;
	waitKey(0);
	return 0;
}

// �ص�����ʵ��
void ShiTomasi_Demo(int, void*)
{
	if (num_corners < 5)
	{
		num_corners = 5;
	}
	vector<Point2f> corners; // ��vector�е�ÿһ��Ԫ�ض���Point2f���͵ģ�OpenCV���ж��壺typedef Point_<float> Point2f; 
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarris = false;
	double k = 0.04;
	Mat result_img = src_img.clone();
	goodFeaturesToTrack(gray_img, corners, num_corners, qualityLevel, minDistance, Mat(), blockSize, useHarris, k);
	printf("��⵽�ǵ����Ŀ:  %d\n", corners.size()); // Vector�����size()�����������е�Ԫ�ظ���

	for (auto t = 0; t < corners.size(); ++t) // ������⵽��ÿһ���ǵ�
	{
		circle(result_img, corners[t], 2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, 0);
	}
	imshow(output_title, result_img);
}


