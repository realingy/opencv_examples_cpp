// ֱ��ͼ���⻯
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
		printf("��ȡͼƬ���� \n");
		return false;
	} 

	//imshow( "ԭʼͼ0", srcImage );

	Mat imageRGB[3];
	split(srcImage, imageRGB);
	for (int i = 0; i < 3; i++)
	{
		equalizeHist(imageRGB[i], imageRGB[i]);
	}
	Mat imageRGBEffect;
	merge(imageRGB, 3, imageRGBEffect);
	//imshow("ֱ��ͼ���⻯ͼ����ǿЧ��", imageRGBEffect);

	cvtColor( srcImage, srcImage, COLOR_BGR2GRAY );
	imshow( "ԭʼͼ", srcImage );

	// ����ֱ��ͼ���⻯
	equalizeHist( srcImage, dstImage );

	imshow( "����ֱ��ͼ���⻯���ͼ", dstImage );

	// ����������˹���ӵ�ͼ����ǿ
	// ʹ������Ϊ5��8����������˹������ͼ�������Դﵽ����ǿͼ���Ŀ��
	// ������˹���ӿ�����ǿ�ֲ���ͼ��Աȶ�	
	Mat imageEnhance;
	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
	filter2D( srcImage, imageEnhance, CV_8UC3, kernel);
	imshow("������˹����ͼ����ǿЧ��", imageEnhance);

	// ���ڶ���Log�任��ͼ����ǿ
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

	//��һ����0~255
	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);

	//ת����8bitͼ����ʾ
	convertScaleAbs(imageLog, imageLog);
	imshow("Log�任", imageLog);

	// �ȴ��û������˳�����
	waitKey(0);
	return 0;

}
#endif

#if 0
//ͳ��ֱ��ͼ
int main()
{
	// ��1������Դͼ��
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
	// ����ֱ��ͼ
	calcHist(&matRGB[0], 1, Channels, Mat(), histB, 1, nHistSize, fHistRanges, true, false);
	calcHist(&matRGB[1], 1, Channels, Mat(), histG, 1, nHistSize, fHistRanges, true, false);
	calcHist(&matRGB[2], 1, Channels, Mat(), histR, 1, nHistSize, fHistRanges, true, false);

	// ����ֱ��ͼ����
	int nHistWidth = 800;
	int nHistHeight = 600;
	int nBinWidth = cvRound((double)nHistWidth / nHistSize[0]);
	Mat matHistImage(nHistHeight, nHistWidth, CV_8UC3, Scalar(255, 255, 255));
	// ֱ��ͼ��һ��
	normalize(histB, histB, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(histG, histG, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(histR, histR, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	// ��ֱ��ͼ�л���ֱ��ͼ
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
	// ��ʾֱ��ͼ
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

	int arraySrcNum[256] = { 0 };                // Դͼ����Ҷ�ͳ�Ƹ���
	int arrayDstNum[256] = { 0 };                // Ŀ��ͼ����Ҷ�ͳ�Ƹ���
	double arraySrcProbability[256] = { 0.0 };   // Դͼ������Ҷȸ���
	double arrayDstProbability[256] = { 0.0 };   // Ŀ��ͼ������Ҷȸ���
	// ͳ��Դͼ��
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			arrayDstNum[matDst.at<uchar>(j, i)]++;
		}
	}
	// ͳ��Ŀ��ͼ��
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
	// �������
	for (int i = 0; i < 256; i++)
	{
		arraySrcProbability[i] = (double)(1.0 * arraySrcNum[i] / nSrcPixNum);
		arrayDstProbability[i] = (double)(1.0 * arrayDstNum[i] / nDstPixNum);
	}
	// ����ֱ��ͼ����ӳ��
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
		arraySrcMap[i] = (int)((L - 1) * dSrcTemp + 0.5);// ��ȥ1��Ȼ����������
		arrayDstMap[i] = (int)((L - 1) * dDstTemp + 0.5);// ��ȥ1��Ȼ����������
	}
	// ����ֱ��ͼƥ��Ҷ�ӳ��
	int grayMatchMap[256] = { 0 };
	for (int i = 0; i < L; i++) // i��ʾԴͼ��Ҷ�ֵ
	{
		int nValue = 0;    // ��¼ӳ���ĻҶ�ֵ
		int nValue_1 = 0;  // ��¼���û���ҵ���Ӧ�ĻҶ�ֵʱ����ӽ��ĻҶ�ֵ
		int k = 0;
		int nTemp = arraySrcMap[i];
		for (int j = 0; j < L; j++) // j��ʾĿ��ͼ��Ҷ�ֵ
		{
			// ��Ϊ����ɢ����£�֮��ͼ���⻯�����Ѿ������ϸ񵥵����ˣ�
			// ���Է��������ܳ���һ�Զ�������������������ƽ����
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
		if (k == 0)// ��ɢ����£�������������Щֵ�Ҳ������Ӧ�ģ�����ȥ��ӽ���һ��ֵ
		{
			nValue = nValue_1;
			k = 1;
		}
		grayMatchMap[i] = nValue / k;
	}
	// ������ͼ��
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
	Mat matSrc = imread(MediaPath + "1.jpg"); // Դͼ��
	Mat matDst = imread(MediaPath + "2.jpg"); // Ŀ��ͼ��

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
