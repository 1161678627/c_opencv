#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<vector>

using namespace std;

// ����ȫ�ֱ��������ڴ洢��ʵ�,{{x,y,color_index},}      0-purple,1-green
vector<vector<int>> allPoints;

// ����ǵ�Ҫ ���˵���ɫ�����ޣ�һ���Ӽ�һ����ɫ�����˳���� hsvmin-hsvmax 6��ȡֵ
vector<vector<int>> myColors = { {68, 203, 59, 132, 255 ,174},
								{124, 48, 117, 143, 170, 255}, // purple
								{68, 72, 156, 102, 126, 255} };	//green

// �Ϸ������hsvɫ���ֵ���������ǻ��Ƶ�ʱ��Ҫ��BGRȥ���ƣ����ӳ��һ��
vector<cv::Scalar> myColorsValues = { {255, 0, 255},	// purple
										{0, 255, 0} };	//green

// Ѱ��ĳ����ɫ�ıʼ� ������Ӿ��Σ�����ñʼ����꣬����
cv::Point getContours(cv::Mat mask, cv::Mat img) {
	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;	// Vec4i��ʾ ��� ��һ��sizeΪ4�Ĵ��int�������ݵ� vector ����

	// �����ĵ�����https://blog.csdn.net/laobai1015/article/details/76400725
	// contours ���ڴ��ÿһ�������ĵ㼯���꣬hierarchy �����������contours��ÿ������������������ϵ��int������CV_RETR_EXTERNALֻ�������Χ������CV_CHAIN_APPROX_SIMPLE �����������Ĺյ���Ϣ
	cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// �ڴ�˳�㶨����ն������Ϻ� �㼯 �ĵ㼯����
	vector<vector<cv::Point>> canPoly(contours.size());

	// ˳�㶨����� ����ͼ�� ��С������ bbox ������
	vector<cv::Rect> boundRect(contours.size());

	// ����һ�� ���� �����ĵ�����
	cv::Point myPoint(0, 0);

	// �ú���ִ����Ϻ�contours �д���� imgDil ͼ�������е� ����Χ���� �� �յ�����
	// ���ǿ��� ��ԭͼ�ϻ�����Щ����������ÿ�������е� �յ㼯 ����ȫ������������opencv�Ѿ���װ���������������������дѭ��ȥ�Լ�������
	// ������������ʾҪ���Ƶ�������ţ�-1��ʾ������������
	// cv::drawContours(img, contours, -1, cv::Scalar(0, 255, 0), 2);

	// ���ڹ������С�ڵ������������Ϊ���Ǹ����������ǵ�������״�Ƚ�С��ʹ�����������
	// �������ÿ�������յ㼯������ contours �е�ÿ������
	for (int i = 0; i < contours.size(); i++)
	{
		// ���㵱ǰ���� ��� ������ ���
		int area = cv::contourArea(contours[i]);
		// cout << area << endl;
		// �ж������С�����������200ʱ���Ż�����������	// ע�����ﲻ�ۼ����ܳ�����������������ؼ����ϵģ���ʵ�ʳߴ粻ֱ�ӹ���
		if (area >= 200)
		{
			// Ȼ�������Щ����������������ܳ�
			float peri = cv::arcLength(contours[i], true);

			// Ȼ��ʹ�ö����Ϻ�������ϼ�⵽��ÿ�������ϵ� �յ㡣���ã���Ҫ�����ǰ�һ�� �����⻬����(�յ㼯) ���߻�����ͼ����������ж�������
			// ��Ҫ��һ����contours �����������շ��ص� ��Ϻ�� contour����Ϻ�� contours ��СС�ڵ��� ԭʼ contours�����ǽ��䶨����ѭ�����ⲿ
			// https://blog.csdn.net/kakiebu/article/details/79824856
			cv::approxPolyDP(contours[i], canPoly[i], 0.02 * peri, true);

			// ͨ����ӡ���ǰ�� ��⵽�� ���� �յ������Կ��������ǰ��̫���ˣ�û��������Щ���ж� �պ��������� ����״������Ϻ�͵���٣������ӽ���ʵ�յ�ֲ�������Σ�
			cout << canPoly[i].size() << " " << contours[i].size() << endl;
			// �����Ƶ�ǰ���ڱ�������� ��� ������
			// ������contours����ʱ�������Ƶĵ�ܶ࣬�������Ƴ�һ���ߣ���������Ϻ��canPoly����ʱ��ÿ��ͼ��������Ƽ���������ߵ㣬�����������Ǻ����������ǵ���״
			// cv::drawContours(img, contours, i, cv::Scalar(0, 255, 0), 2);
			cv::drawContours(img, canPoly, i, cv::Scalar(0, 255, 0), 2);
			cv::Rect boundingbox = cv::boundingRect(canPoly[i]);
			cv::rectangle(img, boundingbox.tl(), boundingbox.br(), cv::Scalar(255, 0, 255), 2);

			// ��myPoint��ֵ
			myPoint.x = boundingbox.x + boundingbox.width / 2;
			myPoint.y = boundingbox.y;
		}
	}
	// ���ɶ��Ŀ����ɫ������û��⵽����myPoint����(0, 0)
	return myPoint;
}



// ��hsvɫ��λĳ����ɫ�ʼ���˶��켣
void findColor(cv::Mat img) {
	cv::Mat imgHsv;
	cv::cvtColor(img, imgHsv, cv::COLOR_BGR2HSV);
	
	// ʹ��һ��ѭ������������ myColors �е� ÿ����ɫ
	for (int i = 0; i < myColors.size(); i++)
	{
		cv::Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		cv::Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		cv::Mat mask;
		cv::inRange(imgHsv, lower, upper, mask);
		// cv::imshow(to_string(i), mask);
		
		// ���ŶԼ��ÿ�� ��ɫ�� ����������þ�׼�� ��ʵ㣬���ݵ�ǰѭ����iȷ�����������ʲô��ɫ�ʵ���ʵ㣬ʹ��һ��point������� ��⵽�ĵ�
		// ֮ǰ����canny��Ե�����ͼ�����ң��������ڶ�ֵ����mask����
		cv::Point tempPoint = getContours(mask, img);

		// ���ɶ��û��⵽������Ĭ�� 0��0�㣬�򲻱���
		if (tempPoint.x != 0 || tempPoint.y != 0)
		{
			// �ۼӴ洢���ӿ�ʼ�����ڣ���⵽��ÿ����ʵ�(����ɫ����i�ж���ɫ)�����ڻ�����������
			allPoints.push_back({ tempPoint.x, tempPoint.y, i });
		}
		
	}
	
}


// ���Ʊʼ�canvas�켣
void drawOnCanvas(cv::Mat img) {
	for (int i = 0; i < allPoints.size(); i++)
	{
		// ��ÿ���ʼ�㻭һ��ʵ��Բ
		cv::circle(img, cv::Point(allPoints[i][0], allPoints[i][1]), 5, myColorsValues[allPoints[i][2]], cv::FILLED);
	}
}



int main() {
	// 0��ʾ���ص�0������ͷ
	cv::VideoCapture cap(0);
	cv::Mat frame;
	int key_code;
	while (true)
	{
		cap.read(frame);
		cv::flip(frame, frame, 1);
		findColor(frame);
		drawOnCanvas(frame);
		cv::imshow("capture", frame);
		key_code = cv::waitKey(1);
		// 27�� esc���ļ���
		if (key_code == 27)
		{
			break;
		}
	}
	cap.release();
	cv::destroyAllWindows();
}