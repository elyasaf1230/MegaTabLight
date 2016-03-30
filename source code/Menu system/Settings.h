#include "../General and Main/General.h"
#include "Page.h"
#include "ChangePassword.h"
#include "FeedBack.h"
#include "Brightness.h"
#include "Sensitivity.h"


#define SENSITIVITY_BUTTON_COLOR 255
#define CHANGEPASSWORD_BUTTON_COLOR	254
#define FEEDBACK_BUTTON_COLOR 253
#define BRIGHTNESS_BUTTON_COLOR 252


class Settings : public Page
{
private:
	//singleton:
	static Settings* s_instance;
	Settings();
	std::unordered_map<Square, Page*> _Actions;

public:
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours);

	//singleton:
	static Settings *instance()
	{
		if (!s_instance)
			s_instance = new Settings();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Settings();
};

