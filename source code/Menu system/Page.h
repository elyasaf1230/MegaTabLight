#include "../General and Main/General.h"

/*
	Basic Asumes: 
			1. All buttons are squares.
			2. 
*/

class Page
{
protected: 
	cv::Mat* _BaseDisplay;	//Base because it is not the final picture, 
							//it can be modified before display(to Screen).
	cv::Mat* _Buttons;		//Input picture from Sensor.
	static std::vector<Page*> functions;	//History of pages.
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours) = 0;


public:
	Page();
	Page(std::string BaseDisplayName, std::string ButtonsName = "");
	~Page();
	Page* Next(cv::Mat* input);
};