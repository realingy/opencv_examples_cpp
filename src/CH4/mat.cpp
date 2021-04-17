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
	//像素操作
	//pixel();

	//Mat操作
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
	Mat A, C; //仅创建信息头部分
	A = imread(MediaPath + "1.jpg");
	C = A; //赋值运算符，A和C的矩阵指针指向相投的矩阵，对一个对象的操作会影响到另一个
	Mat B(C); //拷贝构造函数
	Mat D = A.clone(); //拷贝构造函数

	rectangle(C, cvPoint(100, 200), cvPoint(300, 400), Scalar(0, 0, 255), 1, 1, 0); //对C对象进行操作
	rectangle(B, cvPoint(200, 300), cvPoint(400, 500), Scalar(255, 0, 255), 1, 1, 0); //对B对象进行操作
	rectangle(D, cvPoint(250, 350), cvPoint(450, 550), Scalar(0, 255, 0), 1, 1, 0); //对D对象进行操作

	imshow("A", A); //显示A对象图像
	imshow("B", B); //显示B对象图像
	imshow("C", C); //显示C对象图像
	//结果表明A、B、C对象是同一个对象，或者说操作的是同一个矩阵
	imshow("D", D); //显示D对象图像

	test(D);

	imshow("D", D); //显示D对象图像

	cout << &A << "," << &C;

}

void test(Mat E)
{
	cout << "形参指针地址：" << &E << endl;
	rectangle(E, cvPoint(150, 250), cvPoint(350, 450), Scalar(0, 0, 255), 1, 1, 0); //对E对象进行操作
	imshow("E", E);
}

void test2(Mat & E)
{
	cout << "形参指针地址：" << &E << endl;
	rectangle(E, cvPoint(200, 300), cvPoint(400, 500), Scalar(0, 0, 255), 1, 1, 0); //对E对象进行操作
	imshow("E2", E);
}

void mat2()
{
	Mat A; //仅创建信息头部分
	A = imread(MediaPath + "1.jpg");
	
	rectangle(A, cvPoint(100, 200), cvPoint(300, 400), Scalar(0, 0, 255), 1, 1, 0); //对C对象进行操作

	imshow("A", A); //显示A对象图像

	cout << "实参地址：" << &A << endl;

	test2(A);
	test(A);

	imshow("A", A); //显示A对象图像
}

void pixel()
{
    Mat I = Mat::eye(4, 4, CV_64F);
    I.at<double>(1,1) = CV_PI;
    cout << "\nI = \n" << I << ";\n" << endl;

    Mat r = Mat(10, 3, CV_8UC3);
    randu(r, Scalar::all(0), Scalar::all(255));

    cout << "r (OpenCV默认风格) = " << r << ";" << endl << endl;
    cout << "r (Python风格) = " << format(r, Formatter::FMT_PYTHON) << ";" << endl << endl;
    cout << "r (Numpy风格) = " <<  format(r, Formatter::FMT_NUMPY )<< ";" << endl << endl;
    cout << "r (逗号分隔风格) = " << format(r, Formatter::FMT_CSV   )<< ";" << endl<< endl;
    cout << "r (C语言风格) = " <<  format(r, Formatter::FMT_C     ) << ";" << endl << endl;

    Point2f p(6, 2);
    cout << "【2维点】\np = " << p << ";\n" << endl;

    Point3f p3f(8, 2, 0);
    cout << "【3维点】\np3f = " << p3f << ";\n" << endl;

    vector<float> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);

    cout << "【基于Mat的vector】\nshortvec = " << Mat(v) << ";\n"<<endl;

    vector<Point2f> points(20);
    for (size_t i = 0; i < points.size(); ++i)
        points[i] = Point2f((float)(i * 5), (float)(i % 7));

    cout << "【二维点向量】\npoints = " << points<<";";

}


