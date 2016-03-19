#include "../General and Main/General.h"
#include "Page.h"

class Menu : public Page
{
private:
	//singleton:
	static Menu* s_instance;
	Menu();

public:
	virtual Page* Function(cv::Mat* input);

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