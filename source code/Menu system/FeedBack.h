#include "../General and Main/General.h"
#include "Page.h"

class FeedBack : public Page
{
private:
	//singleton:
	static FeedBack* s_instance;
	FeedBack();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static FeedBack *instance()
	{
		if (!s_instance)
			s_instance = new FeedBack();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~FeedBack();
};