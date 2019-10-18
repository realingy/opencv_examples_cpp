#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "path.h"
using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main()
{
	std::string name = MediaPath + "3.jpg";
    Mat srcImage = imread(name);
    imshow("src",srcImage);

    Mat dstImage;
    dstImage.create(srcImage.rows,srcImage.cols,srcImage.type()); //Ч��ͼ�Ĵ�С��������ԭͼƬ��ͬ

    double time0 = static_cast<double>(getTickCount());

    colorReduce(srcImage, dstImage, 10);

    time0 = ((double)getTickCount() - time0)/getTickFrequency();
    cout<<"����ʱ��: "<<time0<<"s"<<endl;  //�������ʱ��

    imshow("dst",dstImage);

    waitKey(0);
}

//���ر�������ɫ�ռ�����(ȡ��)
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();  //����
    int rowNumber = outputImage.rows;  //����
    int colNumber = outputImage.cols * outputImage.channels(); //����

    for(int i = 0;i < rowNumber;i++)
    {
        uchar* data = outputImage.ptr<uchar>(i);
        for(int j = 0;j < colNumber;j++)
        {
            data[j] = data[j] / div * div + div/2;
        }
    }
}
