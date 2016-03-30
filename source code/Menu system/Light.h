#include "../General and Main/General.h"
#include "Page.h"

#include "LiveWallPaper.h"
#include "WallPaper.h"

#define WALLPAPER_BUTTON_COLOR		255
#define LIVEWALLPAPER_BUTTON_COLOR	254

class Light : public Page
{
private:
	std::unordered_map<Square, Page*> _Actions;
	//singleton:
	static Light* s_instance;
	Light();

public:
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours);

	//singleton:
	static Light *instance()
	{
		if (!s_instance)
			s_instance = new Light();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~Light();
};