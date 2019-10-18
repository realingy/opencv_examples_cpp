#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "path.h"

using namespace std;
using namespace cv;

void pixel();
void mat();
void mat1();
void mat2();
void test(Mat img);

int main()
{
	//���ز���
	//pixel();

	//Mat����
	//mat();

	//mat1();

	mat2();

	waitKey(0);

	return 0;
}

void mat1()
{
	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	cout << "cols: " << Mat(v).cols << ", rows: " << Mat(v).rows << '\n';
	cout << Mat(v) << '\n';
}

void mat()
{
	Mat A, C; //��������Ϣͷ����
	A = imread(MediaPath + "1.jpg");
	C = A; //��ֵ�������A��C�ľ���ָ��ָ����Ͷ�ľ��󣬶�һ������Ĳ�����Ӱ�쵽��һ��
	Mat B(C); //�������캯��
	Mat D = A.clone(); //�������캯��

	rectangle(C, cvPoint(100, 200), cvPoint(300, 400), Scalar(0, 0, 255), 1, 1, 0); //��C������в���
	rectangle(B, cvPoint(200, 300), cvPoint(400, 500), Scalar(255, 0, 255), 1, 1, 0); //��B������в���
	rectangle(D, cvPoint(250, 350), cvPoint(450, 550), Scalar(0, 255, 0), 1, 1, 0); //��D������в���

	imshow("A", A); //��ʾA����ͼ��
	imshow("B", B); //��ʾB����ͼ��
	imshow("C", C); //��ʾC����ͼ��
	//�������A��B��C������ͬһ�����󣬻���˵��������ͬһ������
	imshow("D", D); //��ʾD����ͼ��

	test(D);

	imshow("D", D); //��ʾD����ͼ��

	cout << &A << "," << &C;

}

void test(Mat E)
{
	cout << "�β�ָ���ַ��" << &E << endl;
	rectangle(E, cvPoint(150, 250), cvPoint(350, 450), Scalar(0, 0, 255), 1, 1, 0); //��E������в���
	imshow("E", E);
}

void test2(Mat & E)
{
	cout << "�β�ָ���ַ��" << &E << endl;
	rectangle(E, cvPoint(200, 300), cvPoint(400, 500), Scalar(0, 0, 255), 1, 1, 0); //��E������в���
	imshow("E2", E);
}

void mat2()
{
	Mat A; //��������Ϣͷ����
	A = imread(MediaPath + "1.jpg");
	
	rectangle(A, cvPoint(100, 200), cvPoint(300, 400), Scalar(0, 0, 255), 1, 1, 0); //��C������в���

	imshow("A", A); //��ʾA����ͼ��

	cout << "ʵ�ε�ַ��" << &A << endl;

	test2(A);
	test(A);

	imshow("A", A); //��ʾA����ͼ��
}

void pixel()
{
    Mat I = Mat::eye(4, 4, CV_64F);
    I.at<double>(1,1) = CV_PI;
    cout << "\nI = \n" << I << ";\n" << endl;

    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));

    cout << "r (OpenCVĬ�Ϸ��) = " << r << ";" << endl << endl;
    cout << "r (Python���) = " << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    cout << "r (Numpy���) = " <<  format(r, Formatter::FMT_NUMPY )<< ";" << endl << endl;
    cout << "r (���ŷָ����) = " << format(r, Formatter::FMT_CSV   )<< ";" << endl<< endl;
    cout << "r (C���Է��) = " <<  format(r, Formatter::FMT_C     ) << ";" << endl << endl;

    Point2f p(6, 2);
    cout << "��2ά�㡿\np = " << p << ";\n" << endl;

    Point3f p3f(8, 2, 0);
    cout << "��3ά�㡿\np3f = " << p3f << ";\n" << endl;

    vector<float> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);

    cout << "������Mat��vector��\nshortvec = " << Mat(v) << ";\n"<<endl;

    vector<Point2f> points(20);
    for (size_t i = 0; i < points.size(); ++i)
        points[i] = Point2f((float)(i * 5), (float)(i % 7));

    cout << "����ά��������\npoints = " << points<<";";

}


