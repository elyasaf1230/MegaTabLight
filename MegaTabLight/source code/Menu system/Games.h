#include "../General and Main/General.h"
#include "Page.h"

class Games : public Page
{
private:
	//singleton:
	static Games* s_instance;
	Games();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Games *instance()
	{
		if (!s_instance)
			s_instance = new Games();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Games();
};