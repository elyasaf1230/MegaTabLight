#include "../General and Main/General.h"
#include "Page.h"

class Snake : public Page
{
private:
	//singleton:
	static Snake* s_instance;
	Snake();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Snake *instance()
	{
		if (!s_instance)
			s_instance = new Snake();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Snake();
};