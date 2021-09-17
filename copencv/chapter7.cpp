#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<string>
#include<vector>
#include<iostream>

using namespace std;

void getContours(cv::Mat imgDil, cv::Mat img) {

	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;	// Vec4i��ʾ ��� ��һ��sizeΪ4�Ĵ��int�������ݵ� vector ����

	// �����ĵ�����https://blog.csdn.net/laobai1015/article/details/76400725
	// contours ���ڴ��ÿһ�������ĵ㼯���꣬hierarchy �����������contours��ÿ������������������ϵ��int������CV_RETR_EXTERNALֻ�������Χ������CV_CHAIN_APPROX_SIMPLE �����������Ĺյ���Ϣ
	cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// �ڴ�˳�㶨����ն������Ϻ� �㼯 �ĵ㼯����
	vector<vector<cv::Point>> canPoly(contours.size());

	// ˳�㶨����� ����ͼ�� ��С������ bbox ������
	vector<cv::Rect> boundRect(contours.size());

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

			// ������Щ ����ͼ�ε� ��С��Ӿ��Σ�boundingbox
			boundRect[i] = cv::boundingRect(canPoly[i]);
			// ���Ż�����Щ��С������
			cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 255), 5);


			// ����ʹ�� ��Ϻ�Ľ��ٵ� canPoly ���ߵ������ �жϵ�ǰ��������״
			int objCor = (int)canPoly[i].size();
			string objType;
			if (objCor == 3)
			{
				objType = "Tri";
			}
			else if (objCor == 4)
			{
				// �ǵ�Ϊ4�����ж��ǳ����λ���������
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspRatio >= 0.95 && aspRatio <= 1.05)
				{
					objType = "Square";
				}
				else
				{
					objType = "Rect";
				}
			}
			else
			{
				objType = "Circle";
			}
			// ������Ӿ��ε����Ͻǣ�ƫ��5�����ص�λ�ã�д��������
			cv::putText(img, objType, { boundRect[i].x ,boundRect[i].y - 5 }, cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(255, 255, 0));
		}
	}

}




int main() {

	// ��״��⣬�����Σ�Բ�Σ������εȵ�

	string path = "./Resources/shapes.png";
	cv::Mat img;
	img = cv::imread(path);

	// preprocess
	cv::Mat imgGray, imgBlur, imgCanny, imgDil;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);
	// ��ȡcanny��Ե֮���������һ�£���Ȼ��ȡ�ı�Ե���ܻ��б߽Ƿָû����ȫ����һ���γ�һ���պ���ͨ����
	cv::Mat kernal = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernal);

	// �����ʹ�����canny��Ե����getContours��������һ����������������ꡢ�߽ǵ����꣬���==
	getContours(imgDil, img);

	cv::imshow("img", img);
	cv::imshow("imgCanny", imgDil);
	cv::waitKey(0);

	return 0;
}