#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

using namespace std;

int main() {

	string path = "Resources/cards.jpg";
	cv::Mat img = cv::imread(path);

	// ����任������״Ť���ľ���ͼ����ӳ��Ϊ�������
	// King
	// ���ȶ��������㼯��src��ʾ Ť��ͼ����ԭͼ�ϵ��ĸ�����㣬dst��ʾӳ������img�϶�Ӧ���ĸ�����㣬��Ϊ�м�Ҫ����任���󣬻��г������㣬��˶���ΪPoint2f
	cv::Point2f src[4] = { {529, 142}, {771, 190}, {405, 395}, {674, 457} };
	// ����Ŀ����εĴ�С,���ǵ�ӳ��Ҳ����Ϊfloat����
	float w = 250, h = 350;
	// src��ʾӳ������ͼ���ĸ������꣬��Ϊ���ǽ���ͼ�����»���һ��ͼ��������ʼ�������� (0��0)
	cv::Point2f dst[4] = { {0.0f,0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };	
	// ��任����
	cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
	// ��ʼ�任,����һ���洢�任���������mat
	cv::Mat imgWarp;
	cv::warpPerspective(img, imgWarp, matrix, cv::Size(w, h));

	// Queen
	cv::Point2f src2[4] = { {64, 324}, {338, 277}, {87, 635}, {404, 574} };
	cv::Point2f dst2[4] = { {0.0f,0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };
	matrix = cv::getPerspectiveTransform(src2, dst2);
	cv::warpPerspective(img, imgWarp, matrix, cv::Size(w, h));

	// չʾ�ĸ��Ƕ�λ���,���Ը�����жϵ�ĵ�����ʽ
	for (int i = 0; i < 4; i++)
	{
		// src ��һ�� point ���飬�����Ԫ����point
		cv::circle(img, src[i], 5, cv::Scalar(0, 0, 255), cv::FILLED);
	}

	cv::imshow("imgWarp", imgWarp);
	cv::imshow("img", img);
	cv::waitKey(0);
	return 0;
}