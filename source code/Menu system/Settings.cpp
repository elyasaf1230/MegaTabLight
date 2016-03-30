#include "Settings.h"


/*
Constructor.
*/
Settings::Settings() : Page(PICTURE_SETTINGS, BUTTONS_SETTINGS)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(*this->_Buttons, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (std::vector<std::vector<cv::Point>>::iterator it = contours.begin(); it < contours.end(); ++it)
	{
		Square temp(it->front(), it->back());

		switch (this->_Buttons->at<uchar>(it->front()))
		{
		case CHANGEPASSWORD_BUTTON_COLOR:	this->_Actions[temp] = ChangePassword::instance();	break;
		case FEEDBACK_BUTTON_COLOR:		this->_Actions[temp] = FeedBack::instance();			break;
		case BRIGHTNESS_BUTTON_COLOR:		this->_Actions[temp] = Brightness::instance();		break;
		case SENSITIVITY_BUTTON_COLOR:		this->_Actions[temp] = Sensitivity::instance();		break;

		default:	break;
		}
	}
}


/*
Distructor.
*/
Settings::~Settings()
{

}


Page* Settings::Function(std::vector<std::vector<cv::Point>> *contours)
{
	//asum there is more then one press the program will ignore the presses.
	if (contours->capacity() == 1)
		for (std::unordered_map<Square, Page*>::iterator it = _Actions.begin(); it != _Actions.end(); ++it)
			if (it->first.inBetween((*contours)[0][0])) //if contour is in current button.
				return it->second;
	return this;
}
