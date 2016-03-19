#include "../General and Main/General.h"
#include "Page.h"

class Paint : public Page
{
private:
	//singleton:
	static Paint* s_instance;
	Paint();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Paint *instance()
	{
		if (!s_instance)
			s_instance = new Paint();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Paint();
};