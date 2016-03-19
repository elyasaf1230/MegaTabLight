#include "EdditionalFunction.h"


void DetectPlaceTouched(cv::Mat* buttons, cv::Mat* input, std::vector<std::vector<cv::Point>> *contours)
{
	cv::Mat* result;
	cv::resize(*result, *result, ScreenSize());

	//filtering expected touches.
	int cols = ScreenSize().width, rows = ScreenSize().height;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//if press or drag.
			if ((buttons->at<uchar>(i, j) == PRESS &&
				input->at<uchar>(i, j) <= MAX_PRESS && input->at<uchar>(i, j) > PressSpectrum()) ||
				(buttons->at<uchar>(i, j) == DRAG &&
				input->at<uchar>(i, j) <= PressSpectrum() && input->at<uchar>(i, j) > IgnoreSpectrum()))
				result->at<uchar>(i, j) = buttons->at<uchar>(i, j);
			else
				result->at<uchar>(i, j) = IGNORE;
		}
	}

	//get contours.
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(*result, *contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
}