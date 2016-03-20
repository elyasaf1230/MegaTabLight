#include "../General and Main/General.h"
#include "Page.h"

class Hockey : public Page
{
private:
	//singleton:
	static Hockey* s_instance;
	Hockey();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Hockey *instance()
	{
		if (!s_instance)
			s_instance = new Hockey();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Hockey();
};