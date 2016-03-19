#include "../General and Main/General.h"
#include "Page.h"

class Mouse : public Page
{
private:
	//singleton:
	static Mouse* s_instance;
	Mouse();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Mouse *instance()
	{
		if (!s_instance)
			s_instance = new Mouse();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Mouse();
};