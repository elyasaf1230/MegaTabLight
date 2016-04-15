#ifndef _WALLPAPER_H_
#define _WALLPAPER_H_

#include "../General and Main/General.h"
#include "Page.h"
#include "Picture.h"
#define NEXT_PAGE_COLOR 255
#define CHOICE_1_COLOR 254
#define CHOICE_2_COLOR 253
#define CHOICE_3_COLOR 252
#define CHOICE_4_COLOR 251
#define PREV_PAGE_COLOR 250

class WallPaper : public Page
{
private:
	std::unordered_map<Square, std::string> _pichoice;  //key - button place. value - name of file. 
	Square _NextButton, _PrevButton;
	//singleton:
	static WallPaper* s_instance;
	WallPaper();
	void Load4FilesNames(bool EncDecFlag = true);

public:
	virtual Page* Function(std::vector<std::vector<cv::Point>> *contours);

	//singleton:
	static WallPaper *instance()
	{
		if (!s_instance)
			s_instance = new WallPaper();
		return s_instance;
	}
	void delete_s_instance()
	{
		if (s_instance)
			delete s_instance;
	}

	~WallPaper();
};
#endif