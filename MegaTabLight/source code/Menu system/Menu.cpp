#include "Menu.h"


/*
Constructor.
*/
Menu::Menu()
{
	switch (switch_on)
	{
	default:
		break;
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
	//asuming there is more then one press the program will ignore the presses.
	if (contours->capacity() == 1)
	{
		
	}
	return this;
}