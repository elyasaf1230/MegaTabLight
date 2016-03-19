#include "../General and Main/General.h"
#include "Page.h"

class GeneralPage : public Page
{
private:
	//singleton:
	static GeneralPage* s_instance;
	GeneralPage();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static GeneralPage *instance()
	{
		if (!s_instance)
			s_instance = new GeneralPage();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~GeneralPage();
};