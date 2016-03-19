#include "Screen.h"


/*
	Constructor.
*/
Screen::Screen() : CommunicationProtocol(true)
{
	//build Welcome:-) picture.
	cv::Mat welcome = cv::imread(PICTURE_WELLCOME);


	this->print(&welcome);
}


/*
	Distructor.
*/
Screen::~Screen()
{
	//build Dead:( picture.
	cv::Mat dead = cv::imread(PICTURE_DEAD);

	this->print(&dead);
	
	/*
	After the "dead" picture is shown -> the program will die ->
	screen should show black image.
	We can impliment(моощ) it in two ways:
	1. Wait untill the program will die, and right before it ends, we will send black image.
	2. Add an option in the Arduino. This option will send to the Arduino an interrupt at the end of the program, 
	   (OR - maybe the Arduino as the raspberry's slave can check if the I2C Master(respeberry) is dead?)
	   and then the Arduino will send the black image.

	What should we choose to do?
	Option 1 seems to be more simple...
	But option 2 seems to be smarter and effective...

	We chose the second option.
	*/
	//we need to send the interrupt to the Arduino...

	//delay() of few seconds...
}


/*
	This mathod sends the given picture to the screen.

	Input:
			Mat* pic - pointer the picture to print to the screen.
			bool h - if true - flip the picture horizontaly.
			bool v - if true - flip the picture verticaly.

	Output:
			int - Error code.
*/
void Screen::print(cv::Mat* pic, bool h = false, bool v = false)
{
	if (h) { this->horizontal_flip(pic); }
	if (v) { this->vertical_flip(pic); }

	
	this->_UpdateThread = new std::thread(this->SendI2C, pic); //if will not work, static function (sendi2c and recivespi)
}


/* 
	This mathod file the given picture horizontaly.

	Input: 
			Mat* pic - pinter the the picture to flip.

	Output: 
			None.
			
*/
void Screen::horizontal_flip(cv::Mat* pic)
{
	cv::flip(*pic, *pic, 0);
}


/*
	This mathod file the given picture verticaly.

	Input:
			Mat* pic - pinter the the picture to flip.

	Output:
			None.

*/
void Screen::vertical_flip(cv::Mat* pic)
{
	cv::flip(*pic, *pic, 1);
}
