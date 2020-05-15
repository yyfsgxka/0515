#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//look  up table（查表）
//pow(I,γ)=I^γ
//伽马
Mat gammaTransform(Mat &src, float k)

{
	//建立查询表数组Lut，size==256 
	unsigned char LUT[256];
	//遍历[0，255] 1.下标值归一化到[0, 1]之间 2.output=input^r 3. Lut[i] = Output * 255
	for (int i = 0; i < 256; i++)

	{
		LUT[i] = saturate_cast<uchar>(pow((float)(i / 255.0),k) * 255.0f);
	}

	Mat result = src.clone();
	if (src.channels() == 1)

	{
		MatIterator_<uchar> iterator = result.begin<uchar>();
		MatIterator_<uchar> iteratorEnd = result.end<uchar>();
		for (; iterator != iteratorEnd; iterator++)
		{
			*iterator = LUT[(*iterator)];
		}
	}
	

	return result;

}
bool EqualizeHist(Mat &srcM, Mat &dstM)

{
	int cn = srcM.channels();
	int w = srcM.cols;
	int h = srcM.rows;
	Mat hsv;
    cvtColor(srcM, hsv, CV_BGR2HSV);
	const int hist_sz = 256;
	int hist[hist_sz];
	//初始化
	memset(hist, 0, sizeof(hist));
	uchar *ptr = hsv.data;
	for (int y = 0; y<h; y++)
	{
		for (int x = 0; x<w; x++)
		{
			int idx = y*w*cn + x*cn + 2;
			hist[ptr[idx]]++;
		}
	}
	float scale = 255.f / (w*h);
	int sum = 0;
	uchar lut[hist_sz + 1];
	for (int i = 0; i < hist_sz; i++)

	{
		sum += hist[i];
		int val = cvRound(sum*scale);
		val = MIN(val, 255);
		val = MAX(val, 0);
		lut[i] = val;
	}

	lut[0] = 0;
	for (int y = 0; y<h; y++)
	{
		for (int x = 0; x<w; x++)

		{

			int idx = y*w*cn + x*cn + 2;

			ptr[idx] = lut[ptr[idx]];

		}

	}
	cvtColor(hsv, dstM, CV_HSV2BGR);

	return true;
}

int main()
{

	
	//练习一伽马矫正
	Mat src = imread("face.jpg");

	//取两种不同的gamma值

	float gamma1 = 3.33f;
	float gamma2 = 0.33f;
	float k1 = 1 / gamma1;
	float k2 = 1 / gamma2;

	Mat result1 = gammaTransform(src, k1);

	Mat result2 = gammaTransform(src, k2);

	imshow("srcImage", src);
	imshow("res1", result1);
	imshow("res2", result2);

	

	//练习二
	Mat dstM;
	Mat srcM = imread("etest.jpg");
	
	imshow("scrM", srcM);

	EqualizeHist(srcM, dstM);
	imshow("dstM", dstM);

	
	//练习三
	Mat inputM = imread("gtest.jpg",0);

	//取两种不同的gamma值

	float gamma3 = 4.55f;
	
	float k3 = 1 / gamma3;


	Mat result3 = gammaTransform(inputM, k3);

	imshow("srcImage", inputM);
	imshow("res3", result3);

	waitKey(0);
	return 0;
	

}