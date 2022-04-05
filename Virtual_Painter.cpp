#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>



void findColor(cv::Mat& frameToProcess);
void findEdges(cv::Mat& frameToProcess, cv::Mat& maskFrame, const int & color);
void draw(cv::Mat& frameToProcess);



std::vector<std::vector<double>> colors{ {161, 179, 88, 255, 88, 255}	//pink
	,									  {22, 28, 73, 255, 102, 255}	   //yellow
	,									  {110, 118, 132, 227, 57, 227} };//dark blue																  // num of inner vectors is num of colors (colors in HSV format)
std::vector<cv::Scalar> outColors{ {127,8,255} // pink
,								   {12,253,250}// yellow
,								   {139,0,0} };//dark blue								//colors for the output in BGR

std::vector<std::vector<int>> myPoints {};


int main() {

	cv::VideoCapture cap(1);

	cv::Mat frame;


	while (true)
	{
		cap.read(frame);
		cv::flip(frame, frame, 1);

		findColor(frame);
		draw(frame);

		cv::imshow("Webcam", frame);
		cv::waitKey(20);
	}

	return 0;
}





void findColor(cv::Mat& frameToProcess) {
	
	cv::Mat HSVFrame,maskFrame;
	cv::Point point;

	cv::cvtColor(frameToProcess, HSVFrame, cv::COLOR_BGR2HSV);

	//hMin, hMax, satMin, satMax, vMin, vMax

	for (int i = 0; i < colors.size(); i++) {

		cv::Scalar upper{ colors[i][1],colors[i][3],colors[i][5] }, lower{ colors[i][0],colors[i][2],colors[i][4] };


		cv::inRange(HSVFrame, lower, upper, maskFrame);
		cv::imshow(std::to_string(i), maskFrame);
		findEdges(frameToProcess, maskFrame,i);
	}
	






}

void findEdges(cv::Mat& frameToProcess,cv::Mat & maskFrame, const int & color)
{



	std::vector<std::vector<cv::Point>> contours {};
	std::vector<cv::Vec4i> hierarchy {};

	float perimeter;
	int area;


	cv::findContours(maskFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
	std::vector<cv::Rect> boundingRect(contours.size());
	cv::Point circlePoint{};
	for (size_t i = 0; i < contours.size(); i++)
	{
		area = cv::contourArea(contours[i]);
		
		if (area > 1000) {
			perimeter = cv::arcLength(contours[i], true);

			cv::approxPolyDP(contours[i], contoursPoly[i], 0.01 * perimeter, true);

			boundingRect[i] = cv::boundingRect(contoursPoly[i]);

			circlePoint = { boundingRect[i].x + boundingRect[i].width / 2 , boundingRect[i].y };
			
			if (circlePoint.x != 0 && circlePoint.y != 0)	myPoints.push_back({ circlePoint.x, circlePoint.y, color });


			cv::rectangle(frameToProcess, boundingRect[i], cv::Scalar(255, 0, 255));

		}	
	}
}

void draw(cv::Mat & frameToProcess)
{
	for (auto& i  : myPoints)
	{ 
		cv::circle(frameToProcess, cv::Point{ i[0],i[1] }, 10, outColors[i[2]], cv::FILLED);
	}
}
