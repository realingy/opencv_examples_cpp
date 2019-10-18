#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include "path.h"
#include <iostream>

using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main( )
{
    string name = MediaPath + "3.jpg";
    Mat srcImage = imread(name);
    imshow("src", srcImage);

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

void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone(); //拷贝实参到临时变量

    //获取迭代器
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); //初始位置的迭代器

    for(; it != outputImage.end<Vec3b>(); ++it)
    {
        (*it)[0] = (*it)[0]/div*div + div/2;
        (*it)[1] = (*it)[1]/div*div + div/2;
        (*it)[2] = (*it)[2]/div*div + div/2;
    }
}
