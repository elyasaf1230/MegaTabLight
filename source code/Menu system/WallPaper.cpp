#include "WallPaper.h"

/*
Constructor.
*/
WallPaper::WallPaper() : Page(START_PICTURE_WALLPAPERS_P, START_PICTURE_WALLPAPERS_B)
{
	//loading buttons.
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(*this->_Buttons, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (std::vector<std::vector<cv::Point>>::iterator it = contours.begin(); it < contours.end(); ++it)
	{
		Square temp(it->front(), it->back());

		switch (this->_Buttons->at<uchar>(it->front()))
		{
		case CHOICE_1_COLOR:		this->_pichoice[temp] = "";		break;
		case CHOICE_2_COLOR:		this->_pichoice[temp] = "";		break;
		case CHOICE_3_COLOR:		this->_pichoice[temp] = "";		break;
		case CHOICE_4_COLOR:		this->_pichoice[temp] = "";		break;
		case NEXT_PAGE_COLOR:		this->_NextButton = temp;		break;
		case PREV_PAGE_COLOR:		this->_PrevButton = temp;		break;

		default:	break;
		}
	}
	Load4FilesNames();

}


/*
Distructor.
*/
WallPaper::~WallPaper()
{

}


Page* WallPaper::Function(std::vector<std::vector<cv::Point>> *contours)
{
	//asum there is more then one press the program will ignore the presses.
	if (contours->capacity() == 1)
	{
		std::unordered_map<Square, std::string>::iterator it;
		for (it = this->_pichoice.begin; it != this->_pichoice.end; ++it)
			if (it->first.inBetween((*contours)[0][0])) //if contour is in current button.
				return Picture::instance();

		if (this->_NextButton.inBetween((*contours)[0][0]))
		{
			this->Load4FilesNames();
			for (int j = 0; j < 4; j++)
			{
				cv::putText(*_BaseDisplay, it->second, cvPoint(j, j),
					cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
			}
			return this;
		}
		if (this->_PrevButton.inBetween((*contours)[0][0]))
		{
			this->Load4FilesNames(false);
			/*cv::putText(_BaseDisplay, it->second, cvPoint(30, 30),                       HOOWWWWW
				FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA); */
			return this;
		}
	}
	return this;
}
void WallPaper::Load4FilesNames(bool EncDecFlag = true)
{
	static int count = 1;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("somewhere in my comp")) != NULL)
	{
		for (int i = 0; i < count * 4 && (ent = readdir(dir)) != NULL; i++)
		{
			//loading buttons.
			std::vector<std::vector<cv::Point>> contours;
			std::vector<cv::Vec4i> hierarchy;
			cv::findContours(*this->_Buttons, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

			for (std::vector<std::vector<cv::Point>>::iterator it = contours.begin(); it < contours.end(); ++it)
			{
				Square temp(it->front(), it->back());

				switch (this->_Buttons->at<uchar>(it->front()))
				{
				case CHOICE_1_COLOR:		this->_pichoice[temp] = ent->d_name;		break;
				case CHOICE_2_COLOR:		this->_pichoice[temp] = ent->d_name;		break;
				case CHOICE_3_COLOR:		this->_pichoice[temp] = ent->d_name;		break;
				case CHOICE_4_COLOR:		this->_pichoice[temp] = ent->d_name;		break;
				default:	break;
				}
			}
		}
	}
	else {
		/* could not open directory */
		perror("haha no such directory :P\n");
	}

	//next or rev?!? : P
	if (EncDecFlag)
		count++;
	else
		count--;
}