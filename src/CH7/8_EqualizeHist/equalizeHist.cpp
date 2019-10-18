// 直方图均衡化
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "path.h"

using namespace cv;

#if 0
int main()
{
	Mat srcImage, dstImage;
	srcImage = imread( MediaPath + "mountain.jpg", 1 );
	if(!srcImage.data ) 
	{
		printf("读取图片错误！ \n");
		return false;
	} 

	//imshow( "原始图0", srcImage );

	Mat imageRGB[3];
	split(srcImage, imageRGB);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(imageRGB[i], imageRGB[i]);
	}
	Mat imageRGBEffect;
	merge(imageRGB, 3, imageRGBEffect);
	//imshow("直方图均衡化图像增强效果", imageRGBEffect);

	cvtColor( srcImage, srcImage, COLOR_BGR2GRAY );
	imshow( "原始图", srcImage );

	// 进行直方图均衡化
	equalizeHist( srcImage, dstImage );

	imshow( "经过直方图均衡化后的图", dstImage );

	// 基于拉普拉斯算子的图像增强
	// 使用中心为5的8邻域拉普拉斯算子与图像卷积可以达到锐化增强图像的目的
	// 拉普拉斯算子可以增强局部的图像对比度	
	Mat imageEnhance;
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
	filter2D( srcImage, imageEnhance, CV_8UC3, kernel);
	imshow("拉普拉斯算子图像增强效果", imageEnhance);

	// 基于对数Log变换的图像增强
	Mat image = imread( MediaPath + "mountain.jpg", 1 );
	Mat imageLog(image.size(), CV_32FC3);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++) {
			imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
			imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
			imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
		}
	}

	//归一化到0~255
	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);

	//转换成8bit图像显示
	convertScaleAbs(imageLog, imageLog);
	imshow("Log变换", imageLog);

	// 等待用户按键退出程序
	waitKey(0);
	return 0;

}
#endif

#if 0
//统计直方图
int main()
{
	// 【1】加载源图像
	Mat matSrc, dstImage;
	matSrc = imread( MediaPath + "mountain.jpg", 1 );
	//std::string strPath = "D:\\MyDocuments\\My Pictures\\OpenCV\\";
	//Mat matSrc = imread(strPath + "panda.jpg");

	Mat matRGB[3];

	split(matSrc, matRGB);
	int Channels[] = { 0 };
	int nHistSize[] = { 256 };
	float range[] = { 0, 255 };
	const float* fHistRanges[] = { range };
	Mat histR, histG, histB;
	// 计算直方图
	calcHist(&matRGB[0], 1, Channels, Mat(), histB, 1, nHistSize, fHistRanges, true, false);
	calcHist(&matRGB[1], 1, Channels, Mat(), histG, 1, nHistSize, fHistRanges, true, false);
	calcHist(&matRGB[2], 1, Channels, Mat(), histR, 1, nHistSize, fHistRanges, true, false);

	// 创建直方图画布
	int nHistWidth = 800;
	int nHistHeight = 600;
	int nBinWidth = cvRound((double)nHistWidth / nHistSize[0]);
	Mat matHistImage(nHistHeight, nHistWidth, CV_8UC3, Scalar(255, 255, 255));
	// 直方图归一化
	normalize(histB, histB, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(histG, histG, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(histR, histR, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	// 在直方图中画出直方图
	for (int i = 1; i < nHistSize[0]; i++)
	{
		line(matHistImage,
			Point(nBinWidth * (i - 1), nHistHeight - cvRound(histB.at<float>(i - 1))),
			Point(nBinWidth * (i), nHistHeight - cvRound(histB.at<float>(i))),
			Scalar(255, 0, 0),
			2,
			8,
			0);
		line(matHistImage,
			Point(nBinWidth * (i - 1), nHistHeight - cvRound(histG.at<float>(i - 1))),
			Point(nBinWidth * (i), nHistHeight - cvRound(histG.at<float>(i))),
			Scalar(0, 255, 0),
			2,
			8,
			0);
		line(matHistImage,
			Point(nBinWidth * (i - 1), nHistHeight - cvRound(histR.at<float>(i - 1))),
			Point(nBinWidth * (i), nHistHeight - cvRound(histR.at<float>(i))),
			Scalar(0, 0, 255),
			2,
			8,
			0);
	}
	// 显示直方图
	imshow("histogram", matHistImage);
//	imwrite(strPath + "histogram.jpg", matHistImage);
	waitKey();
	return 0;
}
#endif

using namespace cv;

bool histMatch_Value(Mat matSrc, Mat matDst, Mat &matRet);
int histogram_Matching();

int main()
{
	histogram_Matching();
	return 0;
}

bool histMatch_Value(Mat matSrc, Mat matDst, Mat &matRet)
{
	if (matSrc.empty() || matDst.empty() || 1 != matSrc.channels() || 1 != matDst.channels())
		return false;
	int nHeight = matDst.rows;
	int nWidth = matDst.cols;
	int nDstPixNum = nHeight * nWidth;
	int nSrcPixNum = 0;

	int arraySrcNum[256] = { 0 };                // 源图像各灰度统计个数
	int arrayDstNum[256] = { 0 };                // 目标图像个灰度统计个数
	double arraySrcProbability[256] = { 0.0 };   // 源图像各个灰度概率
	double arrayDstProbability[256] = { 0.0 };   // 目标图像各个灰度概率
	// 统计源图像
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			arrayDstNum[matDst.at<uchar>(j, i)]++;
		}
	}
	// 统计目标图像
	nHeight = matSrc.rows;
	nWidth = matSrc.cols;
	nSrcPixNum = nHeight * nWidth;
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			arraySrcNum[matSrc.at<uchar>(j, i)]++;
		}
	}
	// 计算概率
	for (int i = 0; i < 256; i++)
	{
		arraySrcProbability[i] = (double)(1.0 * arraySrcNum[i] / nSrcPixNum);
		arrayDstProbability[i] = (double)(1.0 * arrayDstNum[i] / nDstPixNum);
	}
	// 构建直方图均衡映射
	int L = 256;
	int arraySrcMap[256] = { 0 };
	int arrayDstMap[256] = { 0 };
	for (int i = 0; i < L; i++)
	{
		double dSrcTemp = 0.0;
		double dDstTemp = 0.0;
		for (int j = 0; j <= i; j++)
		{
			dSrcTemp += arraySrcProbability[j];
			dDstTemp += arrayDstProbability[j];
		}
		arraySrcMap[i] = (int)((L - 1) * dSrcTemp + 0.5);// 减去1，然后四舍五入
		arrayDstMap[i] = (int)((L - 1) * dDstTemp + 0.5);// 减去1，然后四舍五入
	}
	// 构建直方图匹配灰度映射
	int grayMatchMap[256] = { 0 };
	for (int i = 0; i < L; i++) // i表示源图像灰度值
	{
		int nValue = 0;    // 记录映射后的灰度值
		int nValue_1 = 0;  // 记录如果没有找到相应的灰度值时，最接近的灰度值
		int k = 0;
		int nTemp = arraySrcMap[i];
		for (int j = 0; j < L; j++) // j表示目标图像灰度值
		{
			// 因为在离散情况下，之风图均衡化函数已经不是严格单调的了，
			// 所以反函数可能出现一对多的情况，所以这里做个平均。
			if (nTemp == arrayDstMap[j])
			{
				nValue += j;
				k++;
			}
			if (nTemp < arrayDstMap[j])
			{
				nValue_1 = j;
				break;
			}
		}
		if (k == 0)// 离散情况下，反函数可能有些值找不到相对应的，这里去最接近的一个值
		{
			nValue = nValue_1;
			k = 1;
		}
		grayMatchMap[i] = nValue / k;
	}
	// 构建新图像
	matRet = Mat::zeros(nHeight, nWidth, CV_8UC1);
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			matRet.at<uchar>(j, i) = grayMatchMap[matSrc.at<uchar>(j, i)];
		}
	}
	return true;
}

int histogram_Matching()
{
	//std::string strPath = "D:\\MyDocuments\\My Pictures\\OpenCV\\";
	Mat matSrc = imread(MediaPath + "1.jpg"); // 源图像
	Mat matDst = imread(MediaPath + "2.jpg"); // 目标图像

	Mat srcBGR[3];
	Mat dstBGR[3];
	Mat retBGR[3];
	split(matSrc, srcBGR);
	split(matDst, dstBGR);

	histMatch_Value(srcBGR[0], dstBGR[0], retBGR[0]);
	histMatch_Value(srcBGR[1], dstBGR[1], retBGR[1]);
	histMatch_Value(srcBGR[2], dstBGR[2], retBGR[2]);

	Mat matResult;
	merge(retBGR, 3, matResult);
	imshow("src", matSrc);
	imshow("dst", matDst);
	imshow("Ret", matResult);

	cvWaitKey();
	return 0;
}
