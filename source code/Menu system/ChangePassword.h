#include "../General and Main/General.h"
#include "Page.h"

class ChangePassword : public Page
{
private:
	//singleton:
	static ChangePassword* s_instance;
	ChangePassword();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static ChangePassword *instance()
	{
		if (!s_instance)
			s_instance = new ChangePassword();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~ChangePassword();
};