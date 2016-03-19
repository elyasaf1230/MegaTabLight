#include "../General and Main/General.h"
#include "Page.h"

class Keyboard : public Page
{
private:
	//singleton:
	static Keyboard* s_instance;
	Keyboard();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Keyboard *instance()
	{
		if (!s_instance)
			s_instance = new Keyboard();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Keyboard();
};