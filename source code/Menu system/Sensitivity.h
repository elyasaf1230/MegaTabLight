#include "../General and Main/General.h"
#include "Page.h"

class Sensitivity : public Page
{
private:
	//singleton:
	static Sensitivity* s_instance;
	Sensitivity();

public:
	virtual Page* Function(cv::Mat* input);

	//singleton:
	static Sensitivity *instance()
	{
		if (!s_instance)
			s_instance = new Sensitivity();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Sensitivity();
};