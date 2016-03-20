#include "../General and Main/General.h"


void InitialScreenSize();
void InitialSensorSize();

void DetectPlaceTouched(cv::Mat* buttons, cv::Mat* input, std::vector<std::vector<cv::Point>> *contours);