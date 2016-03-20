#include "../General and Main/General.h"
#include "Page.h"

class WallPaper : public Page
{
private:
	//singleton:
	static WallPaper* s_instance;
	WallPaper();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static WallPaper *instance()
	{
		if (!s_instance)
			s_instance = new WallPaper();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~WallPaper();
};