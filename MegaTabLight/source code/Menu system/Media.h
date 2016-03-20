#include "../General and Main/General.h"
#include "Page.h"

class Media : public Page
{
private:
	//singleton:
	static Media* s_instance;
	Media();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Media *instance()
	{
		if (!s_instance)
			s_instance = new Media();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Media();
};