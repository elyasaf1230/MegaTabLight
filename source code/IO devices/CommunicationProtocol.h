#include "../General and Main/General.h"
#include "../../../gnublin-api-master/gnublin.h"

#define CHIPSELECT_PIN 14 //have no idea why, we sould change it....
#define NUM_OF_MUX_SELECTS 8
#define NUM_OF_CHANNELS 4

#define LARGE_START_X SCREEN_WIDTH*(LARGE-1)
#define MEDIUM_START_X SCREEN_WIDTH*(MEDIUM-1)
#define SMALL_START_X SCREEN_WIDTH*(SMALL-1)

#define START_Y_FIRST 0
#define START_Y_SECOND SCREEN_WIDTH/2 

#define ARDUINO1 0x0
#define ARDUINO2 0x1
#define ARDUINO3 0x2
#define ARDUINO4 0x3
#define ARDUINO5 0x4
#define ARDUINO6 0x5

class CommunicationProtocol
{
private:
	bool _ScreenOrSensor; //True means screen, False means Sensor.
	gnublin_spi _mcp3004;
	
	bool send_num_to_demux(int num);
	
	gnublin_gpio gpio;

	gnublin_i2c _Arduinos;

	bool _finished;
protected:
	int SendI2C(cv::Mat* pic);
	void ReceiveSPI(cv::Mat* pic);

	bool is_finished() { return this->is_finished; }
public:
	CommunicationProtocol(bool ScreenOrSensor);
	~CommunicationProtocol();
};