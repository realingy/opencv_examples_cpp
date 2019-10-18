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
    dstImage.create(srcImage.rows,srcImage.cols,srcImage.type()); //效果图的大小、类型与原图片相同

    double time0 = static_cast<double>(getTickCount());

    colorReduce(srcImage, dstImage, 10);

    time0 = ((double)getTickCount() - time0)/getTickFrequency();
    cout<<"处理时长: "<<time0<<"s"<<endl;  //输出运行时间

    imshow("dst",dstImage);

    waitKey(0);
}

//像素遍历加颜色空间缩减(取样)
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();  //拷贝
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols * outputImage.channels(); //列数

    for(int i = 0;i < rowNumber;i++)
    {
        uchar* data = outputImage.ptr<uchar>(i);
        for(int j = 0;j < colNumber;j++)
        {
            data[j] = data[j] / div * div + div/2;
        }
    }
}
