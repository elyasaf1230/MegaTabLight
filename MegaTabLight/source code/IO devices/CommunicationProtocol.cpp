#include "CommunicationProtocol.h"


/*
	Contructor.
	Initialize the devices. 
*/
CommunicationProtocol::CommunicationProtocol(bool ScreenOrSensor) throw(ConnectionException)
{
	_ScreenOrSensor = ScreenOrSensor;
	int i;

	// first time EVER calling ScreenSize()
	if (ScreenOrSensor)		//if this is a screen...
	{
		//initial the I2C devices.
		if (_Arduinos.setAddress(ARDUINO1) == -1 || _Arduinos.setAddress(ARDUINO2) == -1)		
			throw I2CException();
		else if (_Arduinos.setAddress(ARDUINO3) == -1 || _Arduinos.setAddress(ARDUINO4) == -1)	
			ScreenSize(SCREEN_WIDTH, SCREEN_WIDTH * SMALL);	
		else if (_Arduinos.setAddress(ARDUINO5) == -1 || _Arduinos.setAddress(ARDUINO6) == -1)	
			ScreenSize(SCREEN_WIDTH, SCREEN_WIDTH * MEDIUM);
		else																					
			ScreenSize(SCREEN_WIDTH, SCREEN_WIDTH * LARGE);
	}
	else					//if this is a sensor...
	{
		//initial the SPI device.
		SPIException spi_exception = SPIException();
		//setting speed.
		//calcs: 
		//255(receivers per board) * 2(emitter on, emitter off) * 4(channels on the adc) * 25(frames per second) * 10 (10 bits for each number) = 510000hz = 510khz ~= 0.5mhz
		if (_mcp3004.setSpeed(510000) == -1)
		{
			spi_exception.set_what("Setting SPI speed FAILED!");
			throw spi_exception;
		}

			//setting chipselect pin.
		if (_mcp3004.setCS(CHIPSELECT_PIN) == -1);
		{
			spi_exception.set_what("Setting CS FAILED!");
			throw spi_exception;
		}

		//setting select GPIO pins mode.
		if (gpio.pinMode(SELECT_PIN0, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin0 FAILED!");
			throw spi_exception;
		}
		if (gpio.pinMode(SELECT_PIN1, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin1 FAILED!");
			throw spi_exception;
		}
		if (gpio.pinMode(SELECT_PIN2, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin2 FAILED!");
			throw spi_exception;
		}
		if (gpio.pinMode(SELECT_PIN3, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin3 FAILED!");
			throw spi_exception;
		}
		if (gpio.pinMode(SELECT_PIN4, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin4 FAILED!");
			throw spi_exception;
		}
		if (gpio.pinMode(SELECT_PIN5, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin5 FAILED!");
			throw spi_exception;
		}
		if (gpio.pinMode(SELECT_PIN6, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin6 FAILED!");
			throw spi_exception;
		}
		if (gpio.pinMode(SELECT_PIN7, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on pin7 FAILED!");
			throw spi_exception;
		}

		if (gpio.pinMode(SELECT_ON_OFF_PIN, OUTPUT) == -1)
		{
			spi_exception.set_what("PinMode on select on off pin FAILED!");
			throw spi_exception;
		}
	}
}


/*
	Distructor.
*/
CommunicationProtocol::~CommunicationProtocol()
{
}


/*
	This function provides communication with the Arduino, it will send
	the given picture (Mat) to the Arduino via I2C Protocol.

	Input: 
			Mat* pic - pointer to the wanted picture to send.

	Output: 
			int - Error number.
*/
int CommunicationProtocol::SendI2C(cv::Mat* pic)
{
	this->_finished = false;
	/*thinking :	on every board we have 2 arduinos, which means each one of them controls 15X30 picture.*/

	unsigned char buffer[SCREEN_WIDTH * SCREEN_WIDTH / 2];
	
	switch (ScreenSize().width / SCREEN_WIDTH)
	{
	case LARGE:
		this->_Arduinos.send(ARDUINO6, cv::Mat(*pic, cv::Rect(LARGE_START_X, START_Y_SECOND, SCREEN_WIDTH, SCREEN_WIDTH / 2)).data, SCREEN_WIDTH * (SCREEN_WIDTH / 2));
		this->_Arduinos.send(ARDUINO5, cv::Mat(*pic, cv::Rect(LARGE_START_X, START_Y_FIRST, SCREEN_WIDTH, SCREEN_WIDTH / 2)).data, SCREEN_WIDTH * (SCREEN_WIDTH / 2));
	case MEDIUM:
		this->_Arduinos.send(ARDUINO4, cv::Mat(*pic, cv::Rect(MEDIUM_START_X, START_Y_SECOND, SCREEN_WIDTH, SCREEN_WIDTH / 2)).data, SCREEN_WIDTH * (SCREEN_WIDTH / 2));
		this->_Arduinos.send(ARDUINO3, cv::Mat(*pic, cv::Rect(MEDIUM_START_X, START_Y_FIRST, SCREEN_WIDTH, SCREEN_WIDTH / 2)).data, SCREEN_WIDTH * (SCREEN_WIDTH / 2));
	case SMALL:
		this->_Arduinos.send(ARDUINO2, cv::Mat(*pic, cv::Rect(SMALL_START_X, START_Y_SECOND, SCREEN_WIDTH, SCREEN_WIDTH / 2)).data, SCREEN_WIDTH * (SCREEN_WIDTH / 2));
		this->_Arduinos.send(ARDUINO1, cv::Mat(*pic, cv::Rect(SMALL_START_X, START_Y_FIRST, SCREEN_WIDTH, SCREEN_WIDTH / 2)).data, SCREEN_WIDTH * (SCREEN_WIDTH / 2));
		break;
	default:
		break;
	}

	this->_finished = true;
}


/*
	This function provides communication with the ADC 
	It will get the input picture Drom the ADC via SPI Protocol.

	Input: 
			Mat* pic - pointer to picture to write there.

	Output: 
			None.

*/
void CommunicationProtocol::ReceiveSPI(cv::Mat* pic) //SENSOR
{
	this->_finished = false; // Thread start.
	char bufferOFF[NUM_OF_CHANNELS];
	char bufferON[NUM_OF_CHANNELS];
	char bufferRESULT[NUM_OF_CHANNELS];

	// 1. send number to demux.
	// 2. send power OFF to IR emitters.
	// 3. read from ADC.
	// 4. send power ON to IR emitters.
	// 5. read from ADC.
	// 6. calc result.
	// 7. place in picture.

	//May be better: read all off, read all on, calc.
	int rows_size = SensorSize().height;
	int cols_size = SensorSize().width;

	cv::resize(*pic, *pic, SensorSize());
	

	for (int i = 0; i < rows_size; i++) //rows
	{
		for (int j = 0; j < SENSOR_WIDTH; j++)
		{
			//1.
			send_num_to_demux((i * rows_size) + j);

			//2.
			gpio.digitalWrite(SELECT_ON_OFF_PIN, LOW);

			//3.
			_mcp3004.receive(bufferOFF, NUM_OF_CHANNELS);

			//4. 
			gpio.digitalWrite(SELECT_ON_OFF_PIN, HIGH);

			//5.
			_mcp3004.receive(bufferON, NUM_OF_CHANNELS);

			//6. 
			for (int k = 0; k < NUM_OF_CHANNELS; k++)
				bufferRESULT[k] = bufferON[k] - bufferOFF[k];

			//7.
			switch (cols_size / SENSOR_WIDTH)
			{
			case LARGE:
				pic->at<uchar>(i, j * LARGE) = bufferRESULT[2];
			case MEDIUM:
				pic->at<uchar>(i, j * MEDIUM) = bufferRESULT[1];
			case SMALL:
				pic->at<uchar>(i, j * SMALL) = bufferRESULT[0];
				break;
			default:
				break;
			}
		}
	}
	this->_finished = true; //thread end.
}


/*
	This function getting number to send to the demux.

	Input:
			int location - number from 0 to 255.

	Output:
			bool - True if success, False if else.
*/
bool CommunicationProtocol::send_num_to_demux(int location)
{
	std::bitset<sizeof(int)*CHAR_BIT> bits(location);

	gpio.digitalWrite(SELECT_PIN0, bits[0]);
	gpio.digitalWrite(SELECT_PIN1, bits[1]);
	gpio.digitalWrite(SELECT_PIN2, bits[2]);
	gpio.digitalWrite(SELECT_PIN3, bits[3]);
	gpio.digitalWrite(SELECT_PIN4, bits[4]);
	gpio.digitalWrite(SELECT_PIN5, bits[5]);
	gpio.digitalWrite(SELECT_PIN6, bits[6]);
	gpio.digitalWrite(SELECT_PIN7, bits[7]);

	return true;
}