#include "../General and Main/General.h"
#include "Page.h"

class Picture : public Page
{
private:
	//singleton:
	static Picture* s_instance;
	Picture();

public:
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours);

	//singleton:
	static Picture *instance()
	{
		if (!s_instance)
			s_instance = new Picture();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Picture();

	bool setPic(std::string PicName){ *this->_BaseDisplay = cv::imread(PicName); return this->_BaseDisplay->data == NULL; }
};