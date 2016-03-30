#include "../General and Main/General.h"
#include "Page.h"
#include "Hockey.h"
#include "Paint.h"
#include "Snake.h"

#define HOCKEY_BUTTON_COLOR 255
#define PAINT_BUTTON_COLOR	254
#define SNAKE_BUTTON_COLOR	253

class Games : public Page
{
private:
	std::unordered_map<Square, Page*> _Actions;

	//singleton:
	static Games* s_instance;
	Games();
	
public:
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours);

	//singleton:
	static Games *instance()
	{
		if (!s_instance)
			s_instance = new Games();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Games();
};