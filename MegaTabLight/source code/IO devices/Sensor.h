/*
	To create a sensor and use it -> call instance() mathod.
	After creating sensor _mat1 & _mat2 will update over and over again in new thread (update_mat() mathod).
	To get the latest scanned picture -> call scan() mathod.
	To delete the screen -> call delete_s_instance() mathod.
*/

#include "../General and Main/General.h"
#include "CommunicationProtocol.h"

#define MAT1 true
#define MAT2 false


class Sensor : public CommunicationProtocol
{
	

private: 
	// I/O pictures. 
	cv::Mat _mat1;
	cv::Mat _mat2;
	bool _WM;
	//void convert_to_screen();   - not really nessecery.

	//singleton:
	static Sensor* s_instance;
	Sensor();
	std::thread* _UpdateThread;
	std::mutex _mat1_lock, _mat2_lock;
public:
	void scan(cv::Mat* mat);

	//singleton:
	static Sensor *instance()
	{
		if (!s_instance)
			s_instance = new Sensor();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}
	
	~Sensor();

	/////////////////////////////////////////////
	void update_mat();

};

void GettingToit()
{
	Sensor::instance()->update_mat();
}