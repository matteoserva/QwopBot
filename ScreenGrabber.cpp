#include "ScreenGrabber.h"
#include <X11/Xutil.h>
#include <cstring>
ScreenGrabber::ScreenGrabber()
{
	display = XOpenDisplay(nullptr);
		
	setRectangle(0,0,0,0);
}
ScreenGrabber::ScreenGrabber(int x,int y,int width,int height)
{
	display = XOpenDisplay(nullptr);
		
	setRectangle(x,y,width,height);
	
}
/*
void ScreenGrabber::ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel)
{



	XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
	BitsPerPixel = img->bits_per_pixel;
	Pixels.resize(Width * Height * 4);

	memcpy(&Pixels[0], img->data, Pixels.size());

	XFree(img);
}
*/
void ScreenGrabber::getScreenSize(int &width,int &height)
{
	Window root = DefaultRootWindow(display);
		XWindowAttributes attributes = {0};
		XGetWindowAttributes(display, root, &attributes);

		width = attributes.width;
		height = attributes.height;
}
void ScreenGrabber::setRectangle(int x,int y,int width,int height)
{
	this-> x = x;
	this -> y = y;
	this-> width = width;
	this -> height = height;
		if(width <= 0 || height <= 0) {
			getScreenSize(this->width,this->height);
		x=0;
		y=0;
	}
}
void ScreenGrabber::setRectangle(cv::Rect rect)
{
	setRectangle(rect.x,rect.y,rect.width,rect.height);
}
cv::Mat ScreenGrabber::getNextFrame()
{
	Window root = DefaultRootWindow(display);
	XImage* img = XGetImage(display, root, x, y , width, height, AllPlanes, ZPixmap);
	
	
	cv::Mat frame(height,width,img->bits_per_pixel > 24 ? CV_8UC4 : CV_8UC3,img->data);
	
	cv::Mat frame2 = frame.clone();
	XDestroyImage(img);
	return frame2;
}

ScreenGrabber::~ScreenGrabber()
{
	XCloseDisplay(display);
}
