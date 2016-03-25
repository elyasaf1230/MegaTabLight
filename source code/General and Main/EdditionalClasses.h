#ifndef _EDDITIONALCLASSES_
#define _EDDITIONALCLASSES_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

class Square
{
public: 
	cv::Point _start;
	cv::Point _end;
	
	Square(cv::Point start, cv::Point end){
		this->_start = start;
		this->_end = end;
	};
	Square(Square& other){
		this->_start = other._start;
		this->_end = other._end;
	}

	bool operator==(const Square other) const{
		return this->_start == other._start && this->_end == other._end;
	}

	bool operator!=(const Square other) const{
		return this->_start != other._start || this->_end != other._end;
	}

	bool operator>(const Square other) const{
		return ((this->_start.x - this->_end.x) * (this->_start.y - this->_end.y)) > ((other._start.x - other._end.x) * (other._start.y - other._end.y));
	}

	bool operator<(const Square other) const{
		return ((this->_start.x - this->_end.x) * (this->_start.y - this->_end.y)) < ((other._start.x - other._end.x) * (other._start.y - other._end.y));
	}

	bool inBetween(cv::Point point) const{
		return (this->_start.x <= point.x && this->_end.x >= point.x) && (this->_start.y <= point.y && this->_end.y >= point.y);
	}
};

#endif