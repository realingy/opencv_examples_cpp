#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "path.h"
using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main()
{
    string name = MediaPath + "3.jpg";
    Mat srcImage = imread(name);
    imshow("src",srcImage);

    Mat dstImage;
    dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//效果图的大小、类型与原图片相同

    double time0 = static_cast<double>(getTickCount());

    colorReduce(srcImage,dstImage,32);

    time0 = ((double)getTickCount() - time0)/getTickFrequency();
    cout<<"time: "<<time0<<" seconds"<<endl;  //输出运行时间

    imshow("dst",dstImage);
    waitKey(0);
    return 0;
}

//使用【动态地址运算配合at】方法版本的颜色空间缩减函数
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols;  //列数

    for(int i = 0;i < rowNumber;i++)
    {
        for(int j = 0;j < colNumber;j++)
        {
            outputImage.at<Vec3b>(i,j)[0] =  outputImage.at<Vec3b>(i,j)[0]/div*div + div/2;  //蓝色通道
            outputImage.at<Vec3b>(i,j)[1] =  outputImage.at<Vec3b>(i,j)[1]/div*div + div/2;  //绿色通道
            outputImage.at<Vec3b>(i,j)[2] =  outputImage.at<Vec3b>(i,j)[2]/div*div + div/2;  //红色通道
        }
    }
}
