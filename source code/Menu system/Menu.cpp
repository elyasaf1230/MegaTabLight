#include "Menu.h"


/*
Constructor.
*/
Menu::Menu() : Page(PICTURE_MENU, BUTTONS_MENU)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(*this->_Buttons, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	
	for (std::vector<std::vector<cv::Point>>::iterator it = contours.begin(); it < contours.end(); ++it)
	{
		Square temp(it->front(), it->back());

		switch (this->_Buttons->at<uchar>(it->front()))
		{
		case LIGHT_BUTTON_COLOR:		this->_Actions[temp] = Light::instance();				break;
		case SETTINGS_BUTTON_COLOR:		this->_Actions[temp] = Settings::instance();			break;
		case COMPUTER_CONTROL_BUTTONS:	this->_Actions[temp] = ComputerControl::instance();		break;
		case GAMES_BUTTONS_COLOR:		this->_Actions[temp] = Games::instance();				break;
		default:
			break;
		}
	}
}


/*
Distructor.
*/
Menu::~Menu()
{
	
}


Page* Menu::Function(std::vector<std::vector<cv::Point>> *contours)
{
	//asum there is more then one press the program will ignore the presses.
	if (contours->capacity() == 1)
		for (std::unordered_map<Square, Page*>::iterator it = _Actions.begin(); it != _Actions.end(); ++it)
			if (it->first.inBetween((*contours)[0][0])) //if contour is in current button.
				return it->second;
	return this;
}