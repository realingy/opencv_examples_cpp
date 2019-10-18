#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "path.h"

using namespace cv;

int main()
{
	std::string  path = MediaPath + "girl.jpg";
	Mat girl = imread(path);
//	imshow("1_cartoon", girl);

	//初级图像混合
	std::string dotaPath = MediaPath + "dota.jpg";
	std::string dotaLogoPath = MediaPath + "dota_logo.jpg";
	Mat dota = imread(dotaPath);
	Mat dotaLogo = imread(dotaLogoPath);
	
//	imshow("2_source", dota);
//	imshow("3_logo", dotaLogo);

	//合成的目标图片
	Mat imageROI = dota(Rect(800, 350, dotaLogo.cols, dotaLogo.rows));

	//将logo加到原图上
	addWeighted(imageROI, 0.5, dotaLogo, 0.3, 0., imageROI);

	imshow("4_efect", dota);

	waitKey(0);
}

