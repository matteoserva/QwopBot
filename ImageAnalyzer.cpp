#include "ImageAnalyzer.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Rect findRoi(const vector<Point2f>& polygon, Mat& image)
{

	float xMax = 0;
	float yMax = 0;
	float xMin = image.cols;
	float yMin = image.rows;

	for (unsigned int i = 0; i < polygon.size(); i++) {
		xMax = max(xMax, polygon[i].x);
		yMax = max(yMax, polygon[i].y);
		xMin = min(xMin, polygon[i].x);
		yMin = min(yMin, polygon[i].y);
	}

	float x = max(xMin, 0.0f);
	float y = max(yMin, 0.0f);
	float X = min(xMax, (float) image.cols);
	float Y = min(yMax, (float) image.rows);
	float w = max(0.0f, X - x);
	float h = max(0.0f, Y - y);

	return Rect(x, y, w, h);
}
int findMatches(ObjectFeatures object, ObjectFeatures scene,cv::Mat &H)
{
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match( object.descriptors, scene.descriptors, matches );
	//std::cerr<<"matches: " <<matches.size()<<std::endl;

	double max_dist = 0;
	double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for( int i = 0; i < object.descriptors.rows; i++ ) {
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}
	//printf("-- Max dist : %f \n", max_dist );
	//printf("-- Min dist : %f \n", min_dist );

	min_dist = std::max(10.0,min_dist);
	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector< DMatch > good_matches;

	for( int i = 0; i < object.descriptors.rows; i++ ) {
		if( matches[i].distance < 3*min_dist ) {
			good_matches.push_back( matches[i]);
		}
	}
	//std::cerr <<"good matches" << good_matches.size()<<std::endl;
	if(good_matches.size() < 4)
		return 0;


	//-- Localize the object
	std::vector<Point2f> obj;
	std::vector<Point2f> scenePoints;

	for(unsigned int i = 0; i < good_matches.size(); i++ ) {
		//-- Get the keypoints from the good matches
		obj.push_back( object.keypoints[ good_matches[i].queryIdx ].pt );
		scenePoints.push_back( scene.keypoints[ good_matches[i].trainIdx ].pt );
	}
	H = findHomography( obj, scenePoints, CV_RANSAC );
	return good_matches.size();
}
cv::Rect ImageAnalyzer::searchQwopWindow(cv::Mat scene_object)
{
	ObjectFeatures scene_data(scene_object,3000);
	Mat H;
	if(findMatches(init_screen,scene_data,H) > 90) {

		std::vector<Point2f> obj_corners(4),scene_corners;
		obj_corners[0] = cvPoint(0,0);
		obj_corners[1] = cvPoint( init_screen.trainingImage.cols, 0 );
		obj_corners[2] = cvPoint( init_screen.trainingImage.cols, init_screen.trainingImage.rows );
		obj_corners[3] = cvPoint( 0, init_screen.trainingImage.rows );
		perspectiveTransform( obj_corners, scene_corners, H);
		Rect roi = findRoi(scene_corners,scene_object);


		return roi;
	} else
		return Rect(0,0,0,0);
}
bool ImageAnalyzer::isEndScreen(cv::Mat im_color)
{
	cv::Mat mask,im;
	cvtColor(im_color, im, COLOR_RGB2HSV);
	inRange(im, cv::Scalar(0,40,206),Scalar(20,80,226), mask);
	Canny( mask,mask, 1, 5, 3 );
	vector<vector<Point> > contours;
	findContours( mask, contours, noArray(), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	if(contours.size() > 3)
		return false;
	for(unsigned int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		//std::cerr<<"area: "<<area<<std::endl;
		if(area >74000 && area < 76000)
			return true;
	}
	return false;


}
vector<vector<Point> > ImageAnalyzer::extractContours(cv::Mat mask)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny( mask, canny_output, 1, 5, 3 );
	/// Find contours
	findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	//std::cerr<<"contorni: "<<contours.size()<<std::endl;
	return contours;
}
Mat ImageAnalyzer::filterBody(Mat im)
{
	cv::Mat mask;
	inRange(im, cv::Scalar(120,10,0),Scalar(140,255,255), mask);
	Mat element = getStructuringElement( MORPH_ELLIPSE,Size( 8, 8 ) );
	erode(mask,mask,element);
	dilate(mask,mask,element);
	return mask;
}

Mat ImageAnalyzer::filterShoesAndSign(Mat im)
{
	Mat mask;


	inRange(im, cv::Scalar(000,10,100),Scalar(250,80,255), mask);

	Mat element = getStructuringElement( MORPH_ELLIPSE,
	                                     Size( 6, 6) );

	erode(mask,mask,element);
	element = getStructuringElement( MORPH_ELLIPSE,
	                                 Size( 8, 8) );
	dilate(mask,mask,element);
	

	return mask;
}

Mat ImageAnalyzer::filterHair(Mat im)
{
	cv::Mat mask;
	inRange(im, cv::Scalar(0,100,0),Scalar(180,255,55), mask);
	Mat element = getStructuringElement( MORPH_ELLIPSE,Size( 3, 3 ) );
	erode(mask,mask,element);
	element = getStructuringElement( MORPH_ELLIPSE,Size( 10, 10 ) );

	dilate(mask,mask,element);

	return mask;
}

void ImageAnalyzer::drawContours(cv::Mat &image,std::vector<std::vector<cv::Point> >& contours)
{
	//static RNG rng(12345);
	for(unsigned  int i = 0; i< contours.size(); i++ ) {
		Scalar color = Scalar( 10,128,128 );
		cv::drawContours( image, contours, i, color, 2, 8 );
	}
}
bool ImageAnalyzer::keepBiggestContours(std::vector<std::vector<cv::Point> > & contours,unsigned int num)
{
	if(contours.size() < num)
		return false;

	if(contours.size() == num)
		return true;

	std::vector<double> areas;
	areas.resize(contours.size());
	for(unsigned int i = 0; i < contours.size(); i++)
		areas[i] = contourArea(contours[i]);

	while(areas.size() > num) {
		double minArea= 1000000.0;
		unsigned int index = 0;
		for(unsigned int i = 0; i < areas.size(); i++) {
			if(areas[i]< minArea) {
				minArea = areas[i];
				index = i;
			}

		}
		areas.erase(areas.begin() + index);
		contours.erase(contours.begin()+ index);
	}

	return true;
}

void ImageAnalyzer::fillResult(std::vector<std::pair<char,cv::Point> > & result,char type,std::vector<std::vector<cv::Point> > &contours)
{
	for(unsigned int i = 0; i<contours.size(); i++) {
		Moments m = moments( contours[i], false );
		Point com( m.m10/m.m00 , m.m01/m.m00 );
		result.push_back(std::pair<char,Point>(type,com));
	}
}
cv::Mat ImageAnalyzer::filter(cv::Mat scene)
{
	cv::Mat im;
	Mat im_color = scene.rowRange(30,380).colRange(100,500);
	cvtColor(im_color, im, COLOR_RGB2HSV);
	cv::Mat mask;
	cv::Mat mask2;
	inRange(im, cv::Scalar(00,00,200),Scalar(50,5,255), mask);
	inRange(im, cv::Scalar(0,00,0),Scalar(50,200,105), mask2);
	bitwise_or(mask,mask2,mask);
	inRange(im, cv::Scalar(00,100,50),Scalar(90,205,200), mask2);
	bitwise_or(mask,mask2,mask);
	inRange(im, cv::Scalar(0,200,100),Scalar(50,255,255), mask2);
	bitwise_or(mask,mask2,mask);
	inRange(im, cv::Scalar(110,100,200),Scalar(120,255,220), mask2);
	bitwise_or(mask,mask2,mask);
	inRange(im, cv::Scalar(110,200,190),Scalar(120,210,200), mask2);
	bitwise_or(mask,mask2,mask);
	//inRange(im, cv::Scalar(90,150,0),Scalar(180,250,150), mask);//da tenere in or, l'omino


	inRange(im, cv::Scalar(00,150,0),Scalar(90,250,150), mask2);
	bitwise_or(mask,mask2,mask);

	inRange(im, cv::Scalar(70,80,155),Scalar(120,150,215), mask2);
	bitwise_or(mask,mask2,mask);
	Mat element = getStructuringElement( MORPH_ELLIPSE,Size( 6, 6 ) );
	dilate(mask,mask,element);
	element = getStructuringElement( MORPH_ELLIPSE,Size( 6, 6 ) );

	erode(mask,mask,element);
	Mat sub(mask,Rect(0,0,30,40));
	sub.setTo(Scalar::all(255));
	im.setTo(Scalar::all(0),mask);
	//inRange(im, cv::Scalar(90,150,0),Scalar(180,250,150), mask);//da tenere in or, l'omino

	return im;
}
void ImageAnalyzer::saveBackground(cv::Mat immagine)
{
	Mat im;
	cvtColor(immagine,im, COLOR_RGB2HSV);
	background = im.colRange(20,21).clone();
	//imshow("QWOP",background);
	//waitKey(0);
}
void ImageAnalyzer::removeBackground(cv::Mat immagine)
{
	if(immagine.rows != background.rows)
		return;

	int channels = immagine.channels();

	int nRows = immagine.rows;
	int nCols = immagine.cols * channels;
	uchar* p;
	for(int i = 0; i < nRows; ++i) {
		p = immagine.ptr<uchar>(i);
		Vec3b intensity = background.at<Vec3b>(i,0);
		for (int j = 0; j < nCols; j +=channels) {
			if(p[j] == intensity[0] && p[j+1] == intensity[1]&&p[j+2] == intensity[2]) {
				p[j] = p[j+1] = p[j+2] = 0;
			}

		}
	}

	Mat mask;
	inRange(immagine, cv::Scalar(000,00,000),Scalar(180,2,255), mask);
	immagine.setTo(0,mask);

	Mat angolosx = immagine.rowRange(0,100).colRange(0,150);
	angolosx.setTo(0);
	Mat angolodx = immagine.rowRange(0,100).colRange(immagine.cols-150,immagine.cols);
	angolodx.setTo(0);
	{
		Mat mask;
		Mat im2 = immagine.rowRange(immagine.rows-100,immagine.rows);
		inRange(im2, cv::Scalar(110,00,200),Scalar(120,155,255), mask);
		im2.setTo(0,mask);
	}
	inRange(immagine, cv::Scalar(000,00,000),Scalar(1,1,1), mask);
	Mat element = getStructuringElement( MORPH_ELLIPSE,Size( 2, 2 ) );
dilate(mask,mask,element);
immagine.setTo(0,mask);
}
ImageAnalyzer::ImageAnalyzer()
{
	Mat img_object = imread( "/home/matteo/Progetti/QwopBot/references/qwopscreen.png", CV_LOAD_IMAGE_GRAYSCALE );

	imshow("QWOP",img_object);
	waitKey(1);
	init_screen.loadImage(img_object,2000);



}
std::vector<std::pair<char,cv::Point> > ImageAnalyzer::analyzeFrame(cv::Mat &im)
{

	//cv::Mat im ;
	cvtColor(im,im, COLOR_RGB2HSV);
	removeBackground(im);

	std::vector<std::pair<char,cv::Point> > result;

	//Mat im_color =Mat::zeros( im.size(), CV_8UC3 );
	Mat im_color = im;
	{
		Mat mask = filterHair(im);
		vector<vector<Point> > contours = extractContours(mask);
		keepBiggestContours(contours,1);
		drawContours(im_color,contours);
		fillResult(result,'H',contours);
	}
	{
		Mat mask = filterShoesAndSign(im);
		vector<vector<Point> > contours = extractContours(mask);
		keepBiggestContours(contours,4);
		
		drawContours(im_color,contours);
		fillResult(result,'S',contours);
	}
	{
		Mat mask = filterBody(im);
		vector<vector<Point> > contours = extractContours(mask);
		keepBiggestContours(contours,1);
		drawContours(im_color,contours);
		fillResult(result,'B',contours);
	}


	cvtColor(im,im, COLOR_HSV2RGB);

	//imshow("QWOP2",im_color);
	//waitKey(1);




	return result;
}
