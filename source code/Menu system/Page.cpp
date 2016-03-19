#include "Page.h"

/*
	Constructor.
*/
Page::Page(std::string BaseDisplayName, std::string ButtonsName)
{
	*_BaseDisplay = cv::imread(BaseDisplayName);

	if (_BaseDisplay->data == NULL)
		std::cout << "BaseDisplay picture failed to open : " << BaseDisplayName << std::endl;

	*_Buttons = cv::imread(ButtonsName);

	if (_Buttons->data == NULL)
		std::cout << "Buttons picture failed to open : " << ButtonsName << std::endl;

}


/*
	Distructor.
*/
Page::~Page()
{

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

	std::vector<std::vector<cv::Point>> *contours;
	Page* next = NULL;

	//finding contours (touches).
	DetectPlaceTouched(_Buttons, input, contours);

	//Checking if Menu touched.
	for (std::vector<std::vector<cv::Point>>::iterator it = contours->begin(); it < contours->end(); ++it)
	{
		if (std::find(GetMenuButtonPlace().begin(), GetMenuButtonPlace().end(), it->begin) != GetMenuButtonPlace().end()) //detecting Menu press (menu before back).
		{
			next = functions[0];
			functions.clear();

			return next;
		}
		else if (std::find(GetMenuButtonPlace().begin(), GetBackButtonPlace().end(), it->begin) != GetBackButtonPlace().end()) //detecting Back press.
		{
			functions.pop_back(); //pop current.
			next = functions.back();

			return next;
		}
	}

	//call the real function... ^_^
	return this->Function(contours);
}