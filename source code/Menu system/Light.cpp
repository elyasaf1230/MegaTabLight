#include "Light.h"


/*
Constructor.
*/
Light::Light() : Page(PICTURE_LIGHT, BUTTONS_LIGHT)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(*this->_Buttons, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (std::vector<std::vector<cv::Point>>::iterator it = contours.begin(); it < contours.end(); ++it)
	{
		Square temp(it->front(), it->back());

		switch (this->_Buttons->at<uchar>(it->front()))
		{
		case WALLPAPER_BUTTON_COLOR:		this->_Actions[temp] = WallPaper::instance();		break;
		case LIVEWALLPAPER_BUTTON_COLOR:	this->_Actions[temp] = LiveWallPaper::instance();	break;
		default:																				break;
		}
	}
}


/*
Distructor.
*/
Light::~Light()
{

}


Page* Light::Function(std::vector<std::vector<cv::Point>> *contours)
{
	//asum there is more then one press the program will ignore the presses.
	if (contours->capacity() == 1)
		for (std::unordered_map<Square, Page*>::iterator it = _Actions.begin(); it != _Actions.end(); ++it)
			if (it->first.inBetween((*contours)[0][0])) //if contour is in current button.
				return it->second;
	return this;
}