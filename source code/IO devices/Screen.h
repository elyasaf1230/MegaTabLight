#include "../General and Main/General.h"
#include "CommunicationProtocol.h"

class Screen : public CommunicationProtocol
{
private:
	void horizontal_flip(cv::Mat* pic);
	void vertical_flip(cv::Mat* pic);
	
	std::thread* _UpdateThread;
	
	//singleton: 
	static Screen* s_instance;
	Screen();

public: 
	//singleton:
	static Screen *instance()
	{
		if (!s_instance)
			s_instance = new Screen();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Screen();

	void print(cv::Mat* pic, bool h = false, bool v = false);

};