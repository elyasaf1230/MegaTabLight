#include "../General and Main/General.h"
#include "Page.h"

class Movie : public Page
{
private:
	//singleton:
	static Movie* s_instance;
	Movie();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Movie *instance()
	{
		if (!s_instance)
			s_instance = new Movie();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Movie();
};