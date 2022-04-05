#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>


int main() {

	std::string path = "res/test.jpg";

	cv::Mat baseFrame = cv::imread(path),resizedFrame,
		grayScale,
		gaussianBlur,
		canny,
		dilatedFrame,
		erodedFrame;

	cv::resize(baseFrame, resizedFrame, cv::Size(), 0.45, 0.45);


	cv::cvtColor(resizedFrame, grayScale, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(resizedFrame, gaussianBlur, cv::Size(15, 15), 4, 0);
	cv::Canny(gaussianBlur, canny, 50, 150);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::dilate(canny, dilatedFrame, kernel);
	cv::erode(dilatedFrame, erodedFrame, kernel);


	cv::imshow("Base Picture", resizedFrame);
	cv::imshow("Gray scale of Base Picture", grayScale);
	cv::imshow("Gaussian Blur of Base Image", gaussianBlur);
	cv::imshow("Canny filter of Base Image", canny);
	cv::imshow("Dilation of Canny image", dilatedFrame);
	cv::imshow("Erosion of Dilated image", erodedFrame);

	cv::waitKey(0);



	return 0;
}