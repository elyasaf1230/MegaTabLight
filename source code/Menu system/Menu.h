#include "../General and Main/General.h"
#include "Page.h"
#include "Light.h"
#include "ComputerControl.h"
#include "Games.h"
#include "Settings.h"
/*
	Asumes:
		1. Each button has it's color.

*/
#define LIGHT_BUTTON_COLOR			255
#define SETTINGS_BUTTON_COLOR		254
#define COMPUTER_CONTROL_BUTTONS	253
#define GAMES_BUTTONS_COLOR			252


class Menu : public Page
{
private:
	std::unordered_map<Square, Page*> _Actions;

	//singleton:
	static Menu* s_instance;
	Menu();

public:
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours);

	//singleton:
	static Menu *instance()
	{
		if (!s_instance)
			s_instance = new Menu();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Menu();
};