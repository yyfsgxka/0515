#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//look  up table�����
//pow(I,��)=I^��
//٤��
Mat gammaTransform(Mat &src, float k)

{
	//������ѯ������Lut��size==256 
	unsigned char LUT[256];
	//����[0��255] 1.�±�ֵ��һ����[0, 1]֮�� 2.output=input^r 3. Lut[i] = Output * 255
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
	//��ʼ��
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

	
	//��ϰһ٤�����
	Mat src = imread("face.jpg");

	//ȡ���ֲ�ͬ��gammaֵ

	float gamma1 = 3.33f;
	float gamma2 = 0.33f;
	float k1 = 1 / gamma1;
	float k2 = 1 / gamma2;

	Mat result1 = gammaTransform(src, k1);

	Mat result2 = gammaTransform(src, k2);

	imshow("srcImage", src);
	imshow("res1", result1);
	imshow("res2", result2);

	

	//��ϰ��
	Mat dstM;
	Mat srcM = imread("etest.jpg");
	
	imshow("scrM", srcM);

	EqualizeHist(srcM, dstM);
	imshow("dstM", dstM);

	
	//��ϰ��
	Mat inputM = imread("gtest.jpg",0);

	//ȡ���ֲ�ͬ��gammaֵ

	float gamma3 = 4.55f;
	
	float k3 = 1 / gamma3;


	Mat result3 = gammaTransform(inputM, k3);

	imshow("srcImage", inputM);
	imshow("res3", result3);

	waitKey(0);
	return 0;
	

}