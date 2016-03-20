#include "Sensor.h"


/*
	Constructor.
*/
Sensor::Sensor() : CommunicationProtocol(false)
{
	_WM = MAT2;
	this->_UpdateThread = new std::thread(GettingToit/*בחושבים*/);
}


/*
	Distructor.
*/
Sensor::~Sensor()
{
	delete(this->_UpdateThread);
}


/*
	This mathod return the latest scanned picture.

	Input:
			Mat* mat - pointer to picture to store the the picture.

	Output:
			None.
*/
void Sensor::scan(cv::Mat* mat)
{
	cv::resize(*mat, *mat, ScreenSize());

	if (_WM == MAT1)
	{
		this->_mat1_lock.lock();
		//resize , copy and calcs. 

		/*
		May be helpful:
		cv::distanceTransform
		http://docs.opencv.org/master/d7/d1b/group__imgproc__misc.html#ga8a0b7fdfcb7a13dde018988ba3a43042&gsc.tab=0
		http://docs.opencv.org/master/d2/dbd/tutorial_distance_transform.html#gsc.tab=0
		cv::watershed
		http://docs.opencv.org/3.0-rc1/d2/dbd/tutorial_distance_transform.html
		*/
		
//		_mat1->mat;      //just temp right now.

		this->_mat1_lock.unlock();
	}
	else
	{
		this->_mat2_lock.lock();
		//resize , copy and calcs.
//		_mat2->mat;		//just temp right now.

		this->_mat2_lock.unlock();
	}
}


/*
	Mathod to convert the picture from 15X45 to 30X90.

	Input:
			None.

	Output:
			None.
*/
/*void convert_to_screen()
{

}
*/


void Sensor::update_mat()
{
	while (true)
	{
		if (_WM == MAT1)
		{
			//Mutex ON of mat2
			this->_mat2_lock.lock();
			ReceiveSPI(&_mat2);
			//Mutex Off of mat2
			this->_mat2_lock.unlock();
		}
		else
		{
			//Mutex ON of mat1
			this->_mat1_lock.lock();
			ReceiveSPI(&_mat1);
			//Mutex OFF of mat1
			this->_mat1_lock.unlock();
		}

		_WM = !_WM;
	}
}