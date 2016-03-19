#include <exception>

class ConnectionException : public std::exception
{

};


class I2CException : public ConnectionException
{
public:
	virtual const char* what() const throw()
	{
		return "Establish I2C connection failed!";
	}
};

class SPIException : public ConnectionException
{
private:
	string _what = "Establish SPI connection failed!";
public:
	virtual const char* what() const throw()
	{
		return this->_what.c_str();
	}
	void set_what(string newWhat) { this->_what = newWhat; }
};


