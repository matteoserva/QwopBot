#include <vector>
#include <X11/Xlib.h>
#include <cstdint>
#include <opencv/cv.h>
#ifndef _SCREENGRABBER_H_
#define _SCREENGRABBER_H_
class ScreenGrabber
{
	Display* display;
	int x;
	int y;
	int width;
	int height;
	public:
	ScreenGrabber(int,int,int,int);
	void setRectangle(int,int,int,int);
	void setRectangle(cv::Rect);
	~ScreenGrabber();
	ScreenGrabber();
	cv::Mat getNextFrame();
	void getScreenSize(int &width,int &height);

};
#endif