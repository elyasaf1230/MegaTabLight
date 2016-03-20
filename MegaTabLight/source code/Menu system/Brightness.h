#include "../General and Main/General.h"
#include "Page.h"

class Brightness : public Page
{
private:
	//singleton:
	static Brightness* s_instance;
	Brightness();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Brightness *instance()
	{
		if (!s_instance)
			s_instance = new Brightness();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Brightness();
};