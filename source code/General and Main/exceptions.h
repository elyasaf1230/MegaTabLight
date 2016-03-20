#ifndef _EXCEPTIONS_
#define _EXCEPTIONS_

#include <exception>
#include <string>

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
	std::string _what = "Establish SPI connection failed!";
public:
	
	virtual const char* what() const throw()
	{
		return _what.c_str();
	}
	void set_what(std::string newWhat) { _what = newWhat; }
};

#endif


