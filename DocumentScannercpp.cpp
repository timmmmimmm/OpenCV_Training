#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>




cv::Mat preprocessing(cv::Mat frame);


int main() {

	std::string path = "res/paper.jpg";
	std::vector<std::vector<cv::Point>> contours{};

	long area;
	double perimeter;

	cv::Mat frame = cv::imread(path),
			preprocessedFrame = preprocessing(frame),
			contoursFrame;

	cv::findContours(preprocessedFrame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> contourPoly(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		area = cv::contourArea(contours[i]);
		std::cout << "Area: " << area << std::endl;


		if (area > 2000) {

			perimeter = cv::arcLength(contours[i], true);
			
			cv::approxPolyDP(contours[i], contourPoly[i], 0.01 * perimeter, true);

			cv::drawContours(preprocessedFrame, contourPoly, i, cv::Scalar(255, 0, 255), 2);
		}

	}




	cv::imshow("Base Frame",preprocessedFrame);
	
	


	cv::waitKey(0);

	return 0;
}








cv::Mat preprocessing(cv::Mat frame) {

	cv::Mat outFrame;
	cv::resize(frame, frame, cv::Size(0, 0), 0.35, 0.35);

	cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

	cv::GaussianBlur(frame, frame, cv::Size(3, 3), 3, 0);

	cv::Canny(frame, frame, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

	cv::dilate(frame, outFrame, kernel);

	return outFrame;
}