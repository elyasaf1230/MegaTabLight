#include "Page.h"

/*
	Constructor.
*/
Page::Page(std::string BaseDisplayName, std::string ButtonsName)
{
	switch (ScreenSize().width / SCREEN_WIDTH)
	{
	case SMALL:
		BaseDisplayName += "_SMALL";
		ButtonsName += "_SMALL";
		break;
	case MEDIUM:
		BaseDisplayName += "_MEDUIM";
		ButtonsName += "_MEDUIM";
		break;
	case LARGE:
		BaseDisplayName += "_LARGE";
		ButtonsName += "_LARGE";
		break;
	default:
		break;
	}
	BaseDisplayName += PICTURES_FORMAT;
	ButtonsName += PICTURES_FORMAT;

	this->_BaseDisplay = new cv::Mat();
	*_BaseDisplay = cv::imread(BaseDisplayName);

	if (_BaseDisplay->data == NULL)
		std::cout << "BaseDisplay picture failed to open : " << BaseDisplayName << std::endl;

	this->_Buttons = new cv::Mat();
	*_Buttons = cv::imread(ButtonsName);

	if (_Buttons->data == NULL)
		std::cout << "Buttons picture failed to open : " << ButtonsName << std::endl;

}


/*
	Distructor.
*/
Page::~Page()
{
	if (this->_BaseDisplay != NULL)
		delete(this->_BaseDisplay);
	if (this->_Buttons != NULL)
		delete(this->_Buttons);
}


/*
	This function checks if the position of the object is at 'Back' button or 'Menu' button.
	If 'Back' -> return previous Page, if 'Menu' -> return 'Menu' Page.
	Else -> return "Function". 
*/
Page* Page::Next(cv::Mat* input)
{
	//checks if consist in vector.
	if (this != functions.back())
		//appends itself into the vector.
		functions.push_back(this);

	std::vector<std::vector<cv::Point>> *contours = NULL;
	Page* next = NULL;

	//finding contours (touches).
	DetectPlaceTouched(_Buttons, input, contours);
	
	//Checking if Menu touched.
	for (std::vector<std::vector<cv::Point>>::iterator it_contour = contours->begin(); it_contour < contours->end(); ++it_contour)
	{
		for (std::vector<cv::Point>::iterator it_point = it_contour->begin(); it_point < it_contour->end(); ++it_point)
		{
			//detecting Menu press (menu before back).
			if (std::find(GetMenuButtonPlace().begin(), GetMenuButtonPlace().end(), *it_point._Ptr) != GetMenuButtonPlace().end()) 
			{
				next = functions[0];
				functions.clear();

				return next;
			}
			//detecting Back press.
			else if (std::find(GetMenuButtonPlace().begin(), GetBackButtonPlace().end(), *it_point._Ptr) != GetBackButtonPlace().end()) 
			{
				functions.pop_back(); //pop current.
				next = functions.back();

				return next;
			}
		}
	}
	
	//call the real function... ^_^
	return this->Function(contours);
}