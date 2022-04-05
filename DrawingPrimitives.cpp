#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>


int main() {

	cv::Mat frame(cv::Size(800, 800), CV_8UC3, cv::Scalar(0,0,0));


	cv::circle(frame, cv::Point(400, 400), 300, cv::Scalar(0, 69, 255), cv::FILLED);
	
	cv::rectangle(frame, cv::Rect(200, 300, 400, 200), cv::Scalar(255, 255, 255), cv::FILLED);
	
	cv::line(frame, cv::Point(200, 400), cv::Point(600, 400), cv::Scalar(0, 0, 0), 2);

	cv::putText(frame, "OpenCV is pretty cool", cv::Point(200, 400), cv::FONT_HERSHEY_SIMPLEX, 1.16, cv::Scalar(0, 0, 0), 3);
	
	
	cv::imshow("Frame", frame);
	cv::waitKey(0);

	return 0;
}