#include "../General and Main/General.h"
#include "Page.h"

class Settings : public Page
{
private:
	//singleton:
	static Settings* s_instance;
	Settings();

public:
	virtual Page* Function(cv::Mat* input);

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