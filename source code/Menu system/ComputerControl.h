#include "../General and Main/General.h"
#include "Page.h"

class ComputerControl : public Page
{
private:
	//singleton:
	static ComputerControl* s_instance;
	ComputerControl();

public:
	virtual Page* Function(cv::Mat* input);

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