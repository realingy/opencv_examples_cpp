#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "path.h"
using namespace cv;

#define WINDOW_NAME "滑动条的创建&线性混合示例"  //为窗口标题定义的宏

const int g_nMaxAlphaValue = 100; //Alpha值的最大值
int g_nAlphaValueSlider; //滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int ,void *)
{
    //求出当前alpha值相对于最大值的比例
    g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue ;
    //则beta值为1减去alpha值
    g_dBetaValue = ( 1.0 - g_dAlphaValue );

    //根据alpha和beta值进行线性混合
    addWeighted( g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

    //显示效果图
    imshow( WINDOW_NAME, g_dstImage );
}

int main( int argc, char** argv )
{
    //加载图像 (两图像的尺寸需相同)
    std::string name1 = MediaPath + "1.jpg";
    std::string name2 = MediaPath + "1.jpg";
    g_srcImage1 = imread(name1);
    g_srcImage2 = imread(name2);
    if( !g_srcImage1.data ) { 
		std::cout << "读取图片错误\n";
		return -1;
	}
    if( !g_srcImage2.data ) {
		std::cout << "读取图片错误\n";
		return -1;
	}

    //设置滑动条初值为70
    g_nAlphaValueSlider = 70;

    //创建窗体
    namedWindow(WINDOW_NAME, 1);

    //在创建的窗体中创建一个滑动条控件
    char TrackbarName[50];
    sprintf( TrackbarName, "透明值 %d", g_nMaxAlphaValue );

    createTrackbar( TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar );

    //结果在回调函数中显示
    on_Trackbar( g_nAlphaValueSlider, 0 );

    //按任意键退出
    waitKey(0);

    return 0;
}
