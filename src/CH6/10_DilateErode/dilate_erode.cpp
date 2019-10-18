#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "path.h"

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;		//原始图和效果图
int g_nTrackbarNumer = 0;		//0表示腐蚀erode, 1表示膨胀dilate
int g_nStructElementSize = 3;	//结构元素(内核矩阵)的尺寸

void Process();							//膨胀和腐蚀的处理函数
void on_TrackbarNumChange(int, void *);	//回调函数
void on_ElementSizeChange(int, void *);	//回调函数

int main()
{
	system("color 2F");

	g_srcImage = imread(MediaPath + "cat.jpg");
	if( !g_srcImage.data ) { printf("read source image failed！\n"); return 0; }

	namedWindow("【原始图】");
	imshow("【原始图】", g_srcImage);

	namedWindow("【效果图】");
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));
	erode(g_srcImage, g_dstImage, element);
	imshow("【效果图】", g_dstImage);

	createTrackbar("腐蚀/膨胀", "【效果图】", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "【效果图】", &g_nStructElementSize, 21, on_ElementSizeChange);

	cout<<endl<<"\t运行成功，请调整滚动条观察图像效果~\n\n"
		<<"\t按下“q”键时，程序退出。\n";

	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//描述：进行自定义的腐蚀和膨胀操作
void Process() 
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));

	if(g_nTrackbarNumer == 0) {    
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("【效果图】", g_dstImage);
}

//描述：腐蚀和膨胀之间切换开关的回调函数
void on_TrackbarNumChange(int, void *) 
{
	//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}

//描述：腐蚀和膨胀操作内核改变时的回调函数
void on_ElementSizeChange(int, void *)
{
	//内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}

