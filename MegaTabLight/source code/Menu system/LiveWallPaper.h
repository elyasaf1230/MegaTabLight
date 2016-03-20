#include "../General and Main/General.h"
#include "Page.h"

class LiveWallPaper : public Page
{
private:
	//singleton:
	static LiveWallPaper* s_instance;
	LiveWallPaper();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static LiveWallPaper *instance()
	{
		if (!s_instance)
			s_instance = new LiveWallPaper();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~LiveWallPaper();
};