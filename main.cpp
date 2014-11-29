
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

#include "ImageAnalyzer.h"

#include <unistd.h>

using namespace cv;
#include "QwopBot.h"









ObjectFeatures::ObjectFeatures()
{

}
ObjectFeatures::ObjectFeatures(cv::Mat image,int numFeatures)
{
	loadImage(image,numFeatures);
}



void ObjectFeatures::loadImage(cv::Mat image,int numFeatures)
{
	trainingImage=image.clone();
	ORB orb(numFeatures,1.1f,3,8,0,2,ORB::HARRIS_SCORE,8);
	orb(image,Mat(),keypoints,descriptors);


	if(descriptors.type()!=CV_32F)
		descriptors.convertTo(descriptors, CV_32F); // make sure it's CV_32F

	drawKeypoints( trainingImage, keypoints, trainingImage, Scalar::all(255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	//std::cerr <<"descriptors: "<<descriptors.size()<<std::endl;

}



int main()
{
	//inRange(im, cv::Scalar(120,00,000),Scalar(130,255,255), mask); per il corpo
	
	/*Mat im = imread( "/home/matteo/Progetti/QwopBot/references/qwoptest.png" );
	ImageAnalyzer imageAnalyzer;
	cvtColor(im, im, COLOR_RGB2HSV);
	
	imageAnalyzer.saveBackground(im);
	imageAnalyzer.removeBackground(im);
	
	Mat scarpe = imageAnalyzer.filterShoesAndSign(im);
	Mat corpo = imageAnalyzer.filterHair(im);
	
	im.setTo(Scalar(0,255,0),corpo);
	
	//blur( im,im, Size(3,3) );
	//Canny( im,im, 80, 100, 3 );
	
	
	imshow("QWOP",corpo);
	waitKey(0);
	return 0;*/
	nice(1);
	QwopBot bot;
	while(1) {
		bot.step();
		usleep(5000);
	}



	return 0;
}
