#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "path.h"

using namespace cv;
using namespace std;

#define NTESTS 14
#define NITERATIONS 20

void colorReduce0(Mat &image, int div=64)
{
    int rows = image.rows; //行数
    int pixels = image.cols * image.channels(); //每行元素的总元素数量

    for (int j=0; j<rows; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for (int i=0; i<pixels; i++)
        {
            data[i]= data[i]/div*div + div/2;
        }
    }
}

//利用 .ptr 和 * ++
void colorReduce1(Mat &image, int div=64)
{
    int rows = image.rows; //行数
    int pixels = image.cols * image.channels();

    for (int j=0; j<rows; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for (int i=0; i<pixels; i++)
        {
            *data++= *data/div*div + div/2;
        }
    }
}

//利用.ptr 和 * ++ 以及模操作
void colorReduce2(Mat &image, int div=64)
{
    int rows = image.rows; //行数
    int pixels = image.cols * image.channels(); //每行元素的总元素数量

    for (int j=0; j<rows; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for (int i=0; i<pixels; i++)
        {
            int v= *data;
            *data++= v - v%div + div/2;
        }
    }
}

//利用.ptr 和 * ++ 以及位操作
void colorReduce3(Mat &image, int div=64)
{
    int rows = image.rows; //行数
    int pixels = image.cols * image.channels(); //每行元素的总元素数量
    int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));

    //掩码值
    uchar mask= 0xFF<<n; // e.g. 对于 div=16, mask= 0xF0

    for (int j=0; j<rows; j++)
    {
        uchar* data= image.ptr<uchar>(j);
        for (int i=0; i<pixels; i++)
        {
            *data++= *data&mask + div/2;
        }
    }
}


//利用指针算术运算
void colorReduce4(Mat &image, int div=64)
{
    int nl= image.rows; //行数
    int nc= image.cols * image.channels(); //每行元素的总元素数量
    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
    int step= image.step; //有效宽度

    //掩码值
    uchar mask= 0xFF<<n; // e.g. 对于 div=16, mask= 0xF0

    //获取指向图像缓冲区的指针
    uchar *data= image.data;

    for (int j=0; j<nl; j++)
    {
        for (int i=0; i<nc; i++)
        {
            *(data+i)= *data&mask + div/2;
        }
        data+= step;
    }
}

//利用 .ptr 和 * ++以及位运算、image.cols * image.channels()
void colorReduce5(Mat &image, int div=64)
{
    int nl= image.rows; //行数
    int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));

    //掩码值
    uchar mask= 0xFF<<n; // e.g. 例如div=16, mask= 0xF0

    for (int j=0; j<nl; j++)
    {
        uchar* data= image.ptr<uchar>(j);

        for (int i=0; i<image.cols * image.channels(); i++)
        {
            *data++= *data&mask + div/2;
        }
    }
}

//利用.ptr 和 * ++ 以及位运算(continuous)
void colorReduce6(Mat &image, int div=64) {

      int nl= image.rows; //行数
      int nc= image.cols * image.channels(); //每行元素的总元素数量

      if (image.isContinuous())
      {
          //无填充像素
          nc= nc*nl;
          nl= 1;  // 为一维数列
       }

      int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
      //掩码值
      uchar mask= 0xFF<<n; // e.g. 比如div=16, mask= 0xF0

      for (int j=0; j<nl; j++) {
          uchar* data= image.ptr<uchar>(j);
          for (int i=0; i<nc; i++) {
            *data++= *data&mask + div/2;
		  }
      }
}

//利用 .ptr 和 * ++ 以及位运算 (continuous+channels)
void colorReduce7(Mat &image, int div=64) {

      int nl= image.rows; //行数
      int nc= image.cols ; //列数

      if (image.isContinuous())
      {
          //无填充像素
          nc= nc*nl;
          nl= 1;  // 为一维数组
       }

      int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
      //掩码值
      uchar mask= 0xFF<<n; // e.g. 比如div=16, mask= 0xF0

      for (int j=0; j<nl; j++) {
          uchar* data= image.ptr<uchar>(j);
          for (int i=0; i<nc; i++) {
            *data++= *data&mask + div/2;
            *data++= *data&mask + div/2;
            *data++= *data&mask + div/2;
		  }
      }
}

//利用Mat_ iterator
void colorReduce8(Mat &image, int div=64) {

      //获取迭代器
      Mat_<Vec3b>::iterator it= image.begin<Vec3b>();
      Mat_<Vec3b>::iterator itend= image.end<Vec3b>();

      for ( ; it!= itend; ++it) {
        (*it)[0]= (*it)[0]/div*div + div/2;
        (*it)[1]= (*it)[1]/div*div + div/2;
        (*it)[2]= (*it)[2]/div*div + div/2;
      }
}

//利用Mat_ iterator以及位运算
void colorReduce9(Mat &image, int div=64) {

      // div必须是2的幂
      int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
      //掩码值
      uchar mask= 0xFF<<n; // e.g. 比如 div=16, mask= 0xF0

      // 获取迭代器
      Mat_<Vec3b>::iterator it= image.begin<Vec3b>();
      Mat_<Vec3b>::iterator itend= image.end<Vec3b>();

      //扫描所有元素
      for ( ; it!= itend; ++it)
      {
        (*it)[0]= (*it)[0]&mask + div/2;
        (*it)[1]= (*it)[1]&mask + div/2;
        (*it)[2]= (*it)[2]&mask + div/2;
      }
}

//利用Mat Iterator_
void colorReduce10(Mat &image, int div=64) {

      //获取迭代器
      Mat_<Vec3b> cimage= image;
      Mat_<Vec3b>::iterator it=cimage.begin();
      Mat_<Vec3b>::iterator itend=cimage.end();

      for ( ; it!= itend; it++) {
        (*it)[0]= (*it)[0]/div*div + div/2;
        (*it)[1]= (*it)[1]/div*div + div/2;
        (*it)[2]= (*it)[2]/div*div + div/2;
      }
}

//利用动态地址计算配合at
void colorReduce11(Mat &image, int div=64) {

      int nl= image.rows; //行数
      int nc= image.cols; //列数

      for (int j=0; j<nl; j++)
      {
          for (int i=0; i<nc; i++)
          {
                  image.at<Vec3b>(j,i)[0]=	 image.at<Vec3b>(j,i)[0]/div*div + div/2;
                  image.at<Vec3b>(j,i)[1]=	 image.at<Vec3b>(j,i)[1]/div*div + div/2;
                  image.at<Vec3b>(j,i)[2]=	 image.at<Vec3b>(j,i)[2]/div*div + div/2;
		  }
      }
}

//利用图像的输入与输出
void colorReduce12(const Mat &image, Mat &result, int div=64)
{
      int nl= image.rows; //行数
      int nc= image.cols ; //列数

      //准备好初始化后的Mat给输出图像
      result.create(image.rows,image.cols,image.type());

      //创建无像素填充的图像
      nc= nc*nl;
      nl= 1;  //单维数组

      int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
      //掩码值
      uchar mask= 0xFF<<n; // e.g.比如div=16, mask= 0xF0

      for (int j=0; j<nl; j++) {
          uchar* data= result.ptr<uchar>(j);
          const uchar* idata= image.ptr<uchar>(j);
          for (int i=0; i<nc; i++) {
            *data++= (*idata++)&mask + div/2;
            *data++= (*idata++)&mask + div/2;
            *data++= (*idata++)&mask + div/2;
          }
      }
}

//利用操作符重载
void colorReduce13(Mat &image, int div=64) {

      int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
      //掩码值
      uchar mask= 0xFF<<n; // e.g. 比如div=16, mask= 0xF0

      //进行色彩还原
      image=(image&Scalar(mask,mask,mask))+Scalar(div/2,div/2,div/2);
}

string name = MediaPath + "1.jpg";
int main( )
{
    int64 t[NTESTS],tinit;
    Mat image0;
    Mat image1;
    Mat image2;

    system("color 4F");

    image0= imread(name);
    if (!image0.data)
        return 0;

    //时间值设为0
    for (int i=0; i<NTESTS; i++)
        t[i]= 0;


    // 多次重复测试
    int n=NITERATIONS;
    for (int k=0; k<n; k++)
    {
        cout << k << " of " << n << endl;

        image1= imread(name);
        //【方法一】利用.ptr 和 []
        tinit= getTickCount();
        colorReduce0(image1);
        t[0]+= getTickCount()-tinit;

        //【方法二】利用 .ptr 和 * ++
        image1= imread(name);
        tinit= getTickCount();
        colorReduce1(image1);
        t[1]+= getTickCount()-tinit;

        //【方法三】利用.ptr 和 * ++ 以及模操作
        image1= imread(name);
        tinit= getTickCount();
        colorReduce2(image1);
        t[2]+= getTickCount()-tinit;

        //【方法四】 利用.ptr 和 * ++ 以及位操作
        image1= imread(name);
        tinit= getTickCount();
        colorReduce3(image1);
        t[3]+= getTickCount()-tinit;

        //【方法五】 利用指针的算术运算
        image1= imread(name);
        tinit= getTickCount();
        colorReduce4(image1);
        t[4]+= getTickCount()-tinit;

        //【方法六】利用 .ptr 和 * ++以及位运算、image.cols * image.channels()
        image1= imread(name);
        tinit= getTickCount();
        colorReduce5(image1);
        t[5]+= getTickCount()-tinit;

        //【方法七】利用.ptr 和 * ++ 以及位运算(continuous)
        image1= imread(name);
        tinit= getTickCount();
        colorReduce6(image1);
        t[6]+= getTickCount()-tinit;

        //【方法八】利用 .ptr 和 * ++ 以及位运算 (continuous+channels)
        image1= imread(name);
        tinit= getTickCount();
        colorReduce7(image1);
        t[7]+= getTickCount()-tinit;

        //【方法九】 利用Mat_ iterator
        image1= imread(name);
        tinit= getTickCount();
        colorReduce8(image1);
        t[8]+= getTickCount()-tinit;

        //【方法十】 利用Mat_ iterator以及位运算
        image1= imread(name);
        tinit= getTickCount();
        colorReduce9(image1);
        t[9]+= getTickCount()-tinit;

        //【方法十一】利用Mat Iterator_
        image1= imread(name);
        tinit= getTickCount();
        colorReduce10(image1);
        t[10]+= getTickCount()-tinit;

        //【方法十二】 利用动态地址计算配合at
        image1= imread(name);
        tinit= getTickCount();
        colorReduce11(image1);
        t[11]+= getTickCount()-tinit;

        //【方法十三】 利用图像的输入与输出
        image1= imread(name);
        tinit= getTickCount();
        Mat result;
        colorReduce12(image1, result);
        t[12]+= getTickCount()-tinit;
        image2= result;

        //【方法十四】 利用操作符重载
        image1= imread(name);
        tinit= getTickCount();
        colorReduce13(image1);
        t[13]+= getTickCount()-tinit;

        //------------------------------
    }
     //输出图像
    imshow("原始图像",image0);
    imshow("结果",image2);
    imshow("图像结果",image1);

    // 输出平均执行时间
    cout << endl << "-------------------------------------------" << endl << endl;
    cout << "\n【方法一】利用.ptr 和 []的方法所用时间为 " << 1000.*t[0]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法二】利用 .ptr 和 * ++ 的方法所用时间为" << 1000.*t[1]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法三】利用.ptr 和 * ++ 以及模操作的方法所用时间为" << 1000.*t[2]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法四】利用.ptr 和 * ++ 以及位操作的方法所用时间为" << 1000.*t[3]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法五】利用指针算术运算的方法所用时间为" << 1000.*t[4]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法六】利用 .ptr 和 * ++以及位运算、channels()的方法所用时间为" << 1000.*t[5]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法七】利用.ptr 和 * ++ 以及位运算(continuous)的方法所用时间为" << 1000.*t[6]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法八】利用 .ptr 和 * ++ 以及位运算 (continuous+channels)的方法所用时间为" << 1000.*t[7]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法九】利用Mat_ iterator 的方法所用时间为" << 1000.*t[8]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十】利用Mat_ iterator以及位运算的方法所用时间为" << 1000.*t[9]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十一】利用Mat Iterator_的方法所用时间为" << 1000.*t[10]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十二】利用动态地址计算配合at 的方法所用时间为" << 1000.*t[11]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十三】利用图像的输入与输出的方法所用时间为" << 1000.*t[12]/getTickFrequency()/n << "ms" << endl;
    cout << "\n【方法十四】利用操作符重载的方法所用时间为" << 1000.*t[13]/getTickFrequency()/n << "ms" << endl;

    waitKey();
    return 0;
}
