#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//look  up table（查表）
//pow(I,γ)=I^γ
//伽马
Mat gammaTransform(Mat &src, float k)

{
	Mat dstmat;
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


int main()
{

	
	//练习一伽马矫正
	Mat src = imread("face.jpg",0);

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
	Mat img = imread("etest.jpg");
	Mat Channels[3];//0=B,1=G,2=R;
	Mat img_B, img_R, img_G,img_out;
	split(img, Channels);
	equalizeHist(Channels[0], Channels[0]);
	equalizeHist(Channels[1], Channels[1]);
	equalizeHist(Channels[2], Channels[2]);
	merge(Channels, 3,img_out);
	imshow("img_out", img_out);

	/*IplImage *img_in = cvLoadImage("etest.jpg");
	IplImage *img_red = cvCreateImage(cvGetSize(img_in), IPL_DEPTH_8U, 1);	
	IplImage *img_blue = cvCreateImage(cvGetSize(img_in), IPL_DEPTH_8U, 1);	
	IplImage *img_green = cvCreateImage(cvGetSize(img_in), IPL_DEPTH_8U, 1);	
	IplImage *img_out = cvCreateImage(cvGetSize(img_in), IPL_DEPTH_8U, 3);
	cvNamedWindow("img_in", CV_WINDOW_AUTOSIZE);	
	cvShowImage("img_in", img_in); 	
    cvSplit(img_in, img_blue, img_green, img_red, 0); 	
	cvEqualizeHist(img_blue, img_blue);
	cvEqualizeHist(img_green, img_green);	
	cvEqualizeHist(img_red, img_red); 	
	cvMerge(img_blue, img_green, img_red, 0, img_out);	
	cvNamedWindow("img_out", CV_WINDOW_AUTOSIZE);	
	cvShowImage("img_out", img_out);*/

	
	
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