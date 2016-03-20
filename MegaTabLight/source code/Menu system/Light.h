#include "../General and Main/General.h"
#include "Page.h"

class Light : public Page
{
private:
	//singleton:
	static Light* s_instance;
	Light();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Light *instance()
	{
		if (!s_instance)
			s_instance = new Light();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Light();
};