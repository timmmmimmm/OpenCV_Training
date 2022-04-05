#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>



int main() {

	float widht = 250, height = 350;


	std::string path = "res/test_warp.png";

	cv::Mat frame = cv::imread(path),
			warpedFrameK,warpedFrameQ,warpedFrameJ,warpedFrame9;

	cv::Point2f sourceK[4]{ {409,104},{599,142},{312,299},{526,349} },
				sourceQ[4]{ {52,243},{262,207},{69,486},{312,441} },
				sourceJ[4]{ {600,75},{790,58},{649,273},{863,254} },
				source9[4]{ {573,289},{791,330},{500,545},{738,585} },
		destination[4]{ {0.0f,0.0f},{widht,0.0f},{0.0f,height},{widht,height} };


	cv::Mat matrixK = cv::getPerspectiveTransform(sourceK, destination),
			matrixQ = cv::getPerspectiveTransform(sourceQ, destination),
			matrixJ = cv::getPerspectiveTransform(sourceJ, destination),
			matrix9 = cv::getPerspectiveTransform(source9, destination);

	cv::warpPerspective(frame, warpedFrameK, matrixK, cv::Size(widht, height));
	cv::warpPerspective(frame, warpedFrameQ, matrixQ, cv::Size(widht, height));
	cv::warpPerspective(frame, warpedFrameJ, matrixJ, cv::Size(widht, height));
	cv::warpPerspective(frame, warpedFrame9, matrix9, cv::Size(widht, height));

	
	for (auto& i : sourceK) {
		cv::circle(frame, i, 10, cv::Scalar(0, 0, 0), cv::FILLED);
	}
	for (auto& i : sourceQ) {
		cv::circle(frame, i, 10, cv::Scalar(128, 128, 128), cv::FILLED);
	}
	for (auto& i : sourceJ) {
		cv::circle(frame, i, 10, cv::Scalar(0, 0, 255), cv::FILLED);
	}
	for (auto& i : source9) {
		cv::circle(frame, i, 10, cv::Scalar(0, 165, 255), cv::FILLED);
	}


	cv::imshow("Original Frame", frame);
	cv::imshow("the king", warpedFrameK);
	cv::imshow("the queen", warpedFrameQ);
	cv::imshow("the joker", warpedFrameJ);
	cv::imshow("the nine", warpedFrame9);


	cv::waitKey(0);

	return 0;
}