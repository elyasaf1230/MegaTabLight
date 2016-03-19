#ifndef GENERAL_H
#define GENERAL_H
#include <iostream>
#include <bitset>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include "EdditionalFunction.h"
#include "PicturesPlaces.h"
#include "exceptions.h"

#define SCREEN_WIDTH 30
#define SENSOR_WIDTH 15

#define SELECT_PIN0 5			//29
#define SELECT_PIN1 6			//31
#define SELECT_PIN2 12			//32
#define SELECT_PIN3 13			//33
#define SELECT_PIN4 19			//35
#define SELECT_PIN5 16			//36
#define SELECT_PIN6 26			//37
#define SELECT_PIN7 20			//38
#define SELECT_ON_OFF_PIN 21	//40

#define LARGE 3
#define MEDIUM 2
#define SMALL 1

#define MAX_PRESS 255
#define MIN_IGNORE 0
#define PRESS 255
#define DRAG 150
#define IGNORE 0

cv::Size ScreenSize(int Width = SCREEN_WIDTH, int Length = SCREEN_WIDTH * LARGE)
{
	static cv::Size scr_size(Length, Width);
	return scr_size;
}

cv::Size SensorSize(int Width = SENSOR_WIDTH, int Length = SENSOR_WIDTH * LARGE)
{
	static cv::Size sen_size(Length, Width);
	return sen_size;
}

int PressSpectrum(int minimum = 150)
{
	//from minimum to 255
	static int value = minimum;
	return value;
}

int IgnoreSpectrum(int maximum = 50)
{
	//from 0 minimum to maximum
	static int value = maximum;
	return value;
}

std::vector<cv::Point> GetMenuButtonPlace(std::vector<cv::Point> *contour = NULL)
{
	static std::vector<cv::Point> MenuComtour = *contour;
	return MenuComtour;
}

std::vector<cv::Point> GetBackButtonPlace(std::vector<cv::Point> *contour = NULL)
{
	static std::vector<cv::Point> BackComtour = *contour;
	return BackComtour;
}



#endif
