#include "../General and Main/General.h"
#include "Page.h"

class Password : public Page
{
private:
	//singleton:
	static Password* s_instance;
	Password();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Password *instance()
	{
		if (!s_instance)
			s_instance = new Password();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Password();
};