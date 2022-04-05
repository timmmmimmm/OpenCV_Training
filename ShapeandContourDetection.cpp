#define _USE_MATH_DEFINES
#include <cmath>



#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>

void findContours(cv::Mat& frameToProcess, cv::Mat& originalFrame);

int main() {

	std::string path = "res/shapes.jpg";

	cv::Mat frame = cv::imread(path),
			frameGray,
			frameBlured,
			frameCanny,
			frameDilated;

	cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(frameGray, frameBlured, cv::Size(3, 3), 3, 0);
	cv::Canny(frameBlured, frameCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));

	cv::dilate(frameCanny, frameDilated, kernel);


	findContours(frameDilated, frame);


	cv::imshow("Original Frame", frame);
	/*cv::imshow("Grayscale Frame", frameGray);
	cv::imshow("Blurred Grayscale", frameBlured);
	cv::imshow("Canny of frame", frameCanny);
	cv::imshow("Dilation of Canny", frameDilated);*/

	cv::waitKey(0);


	return 0;
}




void findContours(cv::Mat& frameToProcess, cv::Mat& originalFrame) {

	std::vector<std::vector<cv::Point>> contours{};
	std::vector<cv::Vec4i> hierarchy{};
	std::string objectType{};
	
	
	int area{}, numberOfCorners{}, rectArea{};
	float perimeter{}, aspectRatio{}, blankSpace{}, radius{};


	cv::Point2f center{};




	cv::findContours(frameToProcess, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> contoursPoly(contours.size());
	std::vector<cv::Rect> boundRects(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		area = cv::contourArea(contours[i]);

		
		
		if (area > 5000) {
			std::cout << "Area of shape: " << area << std::endl;

			perimeter = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], contoursPoly[i], 0.01 * perimeter, true);

			std::cout << "Number of corners: " << contoursPoly[i].size() << std::endl;


			boundRects[i] = cv::boundingRect(contoursPoly[i]);

			numberOfCorners = contoursPoly[i].size();

			switch (numberOfCorners)
			{
			case 3:
				objectType = "Triangle";
				break;

			case 4:
				aspectRatio = (float)boundRects[i].width / (float)boundRects[i].height;
				std::cout << "Aspect ratio: " << aspectRatio << std::endl;

				rectArea = (boundRects[i].width - 1) * (boundRects[i].height - 1);
				std::cout << "Area of bounding rect: " << rectArea << std::endl;

				if (area == rectArea - 1) {
					if (aspectRatio >= 0.95 && aspectRatio <= 1.05)	objectType = "Square";
					else                                            objectType = "Rectangle";

				}

				else
				{
					if (aspectRatio >= 1)							objectType = "Parallelegram";
					else                                            objectType = "Rhombus";
				}

				break;


			case 6:
				objectType = "Hexagon";
				break;


			case 10:
				rectArea = (boundRects[i].width - 1) * (boundRects[i].height - 1);
				std::cout << "Area of bounding rect: " << rectArea << std::endl;

				blankSpace = (float)(rectArea - area) / (float)rectArea * 100.0f;


				if ((int)blankSpace < 50)	objectType == "Decagon";
				else                        objectType = "Star";

				break;


			default:
				cv::minEnclosingCircle(contoursPoly[i], center, radius);

				rectArea = M_PI * (double)(radius-0.6) * (double)(radius-0.6);
				std::cout << "Area of bounding circle: " << rectArea << std::endl;
					
					
				blankSpace = rectArea - area;

				if (blankSpace < (float)rectArea * 0.01f) {
					objectType = "Circle";
					
					break;
				}
				//cv::circle(originalFrame, center, radius, cv::Scalar(255, 0, 0), 3);
				


				objectType = "Heart";

				break;
			}


			cv::drawContours(originalFrame, contoursPoly, i, cv::Scalar(0, 0, 0), 2);
			cv::rectangle(originalFrame, boundRects[i].tl(), boundRects[i].br(), cv::Scalar(0, 255, 0), 3);
			cv::putText(originalFrame, objectType, { boundRects[i].x, boundRects[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(0, 0, 0), 2);
		}
	}
}