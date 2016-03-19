#include "../General and Main/General.h"
#include "Page.h"

class Shortcut : public Page
{
private:
	//singleton:
	static Shortcut* s_instance;
	Shortcut();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Shortcut *instance()
	{
		if (!s_instance)
			s_instance = new Shortcut();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Shortcut();
};