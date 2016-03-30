#include "../General and Main/General.h"
#include "Page.h"
#include "Media.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Shortcut.h"


#define MOUSE_BUTTON_COLOR 255
#define KEYBOARD_BUTTON_COLOR 254
#define MEDIA_BUTTON_COLOR 253
#define SHORTCUT_BUTTON_COLOR 252

class ComputerControl : public Page
{
private:
	std::unordered_map<Square, Page*> _Actions;

	//singleton:
	static ComputerControl* s_instance;
	ComputerControl();

public:
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours);

	//singleton:
	static ComputerControl *instance()
	{
		if (!s_instance)
			s_instance = new ComputerControl();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~ComputerControl();
};