#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// �����a4ֽ�Ĵ�С
float width = 420;
float height = 596;
int cropSize = 5;

// Ԥ�����õ�������ͼƬ�ı�Ե�����
cv::Mat preProcess(cv::Mat img) {
	// �Ҷ�
	cv::Mat imgGray;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	// ģ��
	cv::Mat imgBlur;
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	// ��Ե���
	cv::Mat imgCanny;
	cv::Canny(imgBlur, imgCanny, 25, 75);
	// ����
	cv::Mat imgDil;
	cv::Mat kernal = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernal);

	// ���ͺ�ı�Ե�������������ڼ������
	return imgDil;
}

// ����������ľ�����������a4ֽ�����ĸ����ص�����
vector<cv::Point> getBiggestContour(cv::Mat imgCanny, cv::Mat imgOriginal) {

	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;
	cv::findContours(imgCanny, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// �������ϵ������洢����
	vector<vector<cv::Point>> canPoly(contours.size());

	// �洢������Ŀ�����������
	vector<cv::Point> biggestPoint;
	// ����Ѱ��������������
	float max_area = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		// ���ﲻ�ܼ���һ��bool����Ϊtrue
		float area = cv::contourArea(contours[i]);
		// cout << area << endl;
		// �����������500�ıպ����������ж�
		if (area > 500)
		{
			float peri = cv::arcLength(contours[i], true);
			// ��������
			cv::approxPolyDP(contours[i], canPoly[i], 0.02 * peri, true);
			// Ŀ������������ڵ�ǰ���ģ�����Ϻ�Ľ���Ǿ��β�����ѡ ocr Ŀ��
			if (area > max_area && canPoly[i].size() == 4)
			{
				max_area = area;
				// ����һ�¶������Ϻ���������
				cv::drawContours(imgOriginal, canPoly, i, cv::Scalar(255, 0, 255), 3);
				biggestPoint = { canPoly[i][0], canPoly[i][1], canPoly[i][2], canPoly[i][3] };
			}
		}	
	}
	// ���û�м�⵽��size��0
	// ��⵽��ԭʼ�������������������ģ���Ҫ�ֶ����ĸ������������������Ŀ���Ǻ�͸�ӱ任�Ǳ߶�Ӧ����
	vector<cv::Point> biggestPointReal(biggestPoint.size());
	if (biggestPoint.size() != 0)
	{
		float max_point = 0;
		int max_index;
		float min_point = 100000;
		int min_index;
		for (int i = 0; i < biggestPoint.size(); i++)
		{
			// ������ ���3 �ĵ㣬x+y ���
			if (biggestPoint[i].x + biggestPoint[i].y > max_point)
			{
				biggestPointReal[3] = { biggestPoint[i].x, biggestPoint[i].y };
				max_point = biggestPoint[i].x + biggestPoint[i].y;
				max_index = i;
			}
			// ���� ���0 �ĵ㣬 x+y ��С
			if (biggestPoint[i].x + biggestPoint[i].y < min_point)
			{
				biggestPointReal[0] = { biggestPoint[i].x, biggestPoint[i].y };
				min_point = biggestPoint[i].x + biggestPoint[i].y;
				min_index = i;
			}
		}
		// �ҵ�ʣ������δ��ɸѡ�ĵ�
		vector<cv::Point> tempPointReal;
		for (int i = 0; i < biggestPoint.size(); i++)
		{
			// �ų����Ѿ�ѡ����0��3��
			if ((biggestPoint[i].x == biggestPointReal[0].x && biggestPoint[i].y == biggestPointReal[0].y) or (biggestPoint[i].x == biggestPointReal[3].x && biggestPoint[i].y == biggestPointReal[3].y))
			{
				continue;
			}
			else
			{
				
				tempPointReal.push_back(biggestPoint[i]);
			}
		}

		// �ұ��Ϊ 1 �ĵ㣬x�Ƚϴ�y�Ƚ�С
		if (tempPointReal[0].x > tempPointReal[1].x)
		{
			biggestPointReal[1] = { tempPointReal[0].x, tempPointReal[0].y };
			biggestPointReal[2] = tempPointReal[1];
		}
		else
		{
			biggestPointReal[1] = tempPointReal[1];
			biggestPointReal[2] = tempPointReal[0];
		}

	}
	return biggestPointReal;
}

// �������ֽ�ŵ��ĸ������ȦȦ�������жϻ�ȡ��׼��׼
void drawPoints(vector<cv::Point> points, cv::Mat imgOriginal) {
	if (points.size() == 0)
	{
		return;
	}

	for (int i = 0; i < points.size(); i++)
	{
		cv::circle(imgOriginal, points[i], 5, cv::Scalar(0, 255, 0), cv::FILLED);
		cv::putText(imgOriginal, to_string(i), cv::Point(points[i].x, points[i].y - 5), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0, 0, 255), 4);
	}
}

// ���͸�ӱ任����ȡa4ֽ����Ϊ������һ�� ���� ͼƬ
cv::Mat processImgWarp(cv::Mat img, vector<cv::Point> biggestPoints) {
	// ����ԭͼ����
	cv::Point2f src[4] = {biggestPoints[0], biggestPoints[1], biggestPoints[2], biggestPoints[3]};
	// �任�����ͼ����
	cv::Point2f dst[4] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, height}, {width, height} };

	// ��任����
	cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
	// ��ʼ�任,����һ���洢�任���������mat
	cv::Mat imgWarp;
	cv::warpPerspective(img, imgWarp, matrix, cv::Size(width, height));
	return imgWarp;
}


int main() {
	string path = "Resources/paper.jpg";
	cv::Mat img = cv::imread(path);
	cv::Mat imgOriginal;
	// ͼ��̫���ˣ���С����Ϊһ��
	// cv::resize(img, img, cv::Size(), 0.5, 0.5);
	img.copyTo(imgOriginal);	// ����img��Ϊ����

	// preprocess
	cv::Mat imgCanny;
	imgCanny = preProcess(imgOriginal);

	// get biggest contour
	vector<cv::Point> biggestPoints = getBiggestContour(imgCanny, imgOriginal);
	drawPoints(biggestPoints, imgOriginal);
	
	// warp
	cv::Mat imgWarp;
	imgWarp = processImgWarp(img, biggestPoints);

	// crop���޼��ڱ�
	cv::Mat imgCrop;
	// roi(x1, x1, w, h);
	cv::Rect roi(cropSize+5, cropSize+5, (int)(width - cropSize*2), (int)(height - cropSize*2));
	imgCrop = imgWarp(roi);

	cv::imshow("imgOriginal", imgOriginal);
	// cv::imshow("image canny", imgCanny);
	cv::imshow("image wrap", imgCrop);
	// cv::imshow("img", img);
	cv::waitKey(0);
	return 0;
}