#include <opencv/cv.h>
#include <vector>
#ifndef _IMAGE_ANALYZER_H_
#define _IMAGE_ANALYZER_H_

class ObjectFeatures
{
public:
	cv::Mat trainingImage;

	ObjectFeatures();
	ObjectFeatures(cv::Mat,int numFeatures = 500);
	std::vector<cv::KeyPoint> keypoints;
	cv::Mat descriptors;
	void loadImage(cv::Mat,int numFeatures = 500);

};
class ImageAnalyzer
{
	std::vector<std::vector<cv::Point> > extractContours(cv::Mat);

	void drawContours(cv::Mat &,std::vector<std::vector<cv::Point> >&);
	bool keepBiggestContours(std::vector<std::vector<cv::Point> > &,unsigned int);
	void fillResult(std::vector<std::pair<char,cv::Point> > & result,char type,std::vector<std::vector<cv::Point> > &contours);

	ObjectFeatures init_screen;
	cv::Mat background;

public:
	cv::Mat filter(cv::Mat);
	cv::Rect findScreen(cv::Mat);
	std::vector<std::pair<char,cv::Point> >  analyzeFrame(cv::Mat&);
	ImageAnalyzer();
	cv::Rect searchQwopWindow(cv::Mat);
	bool isEndScreen(cv::Mat);
	void removeBackground(cv::Mat image);
	void saveBackground(cv::Mat image);
		cv::Mat filterBody(cv::Mat);
	cv::Mat filterHair(cv::Mat);
	cv::Mat filterShoesAndSign(cv::Mat);
};
#endif
