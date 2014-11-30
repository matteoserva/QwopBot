#include "QwopBot.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
void QwopBot::pause(float seconds)
{
	clockStart = Clock::now();
	pauseTime = seconds;
}

bool QwopBot::isPaused()
{
	Clock::time_point t0 = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(t0 - clockStart);
	double elapsed = ms.count() / 1000.0;
	if(elapsed > pauseTime)
		return false;
	return true;


}
QwopBot::QwopBot()
{
	std::cerr <<"Welcome to QwopBot. waiting for qwop screen"<<std::endl;

	status = SEARCHING_WINDOW;


	namedWindow("QWOP");
}
QwopBot::~QwopBot()
{

}
void QwopBot::step()
{
	cv::Mat scene_color = screenGrabber.getNextFrame();





	if(status == SEARCHING_WINDOW) {
		cv::Mat scene_object;
		cvtColor(scene_color,scene_object,CV_BGR2GRAY );
		Rect roi = imageAnalyzer.searchQwopWindow(scene_object);
		if(roi.width * roi.height > 10) {
			status = NEED_RESET;
			std::cerr<<"Window found. Push enter to start"<<std::endl;
			std::cin.get() ;
			keyPresser.focus(roi.x+roi.width/2,roi.y+roi.height/2);

			usleep(500000);
			keyPresser.enterText(" ");
			usleep(500000);
			screenGrabber.setRectangle(roi);
			scene_color = screenGrabber.getNextFrame();
			imageAnalyzer.saveBackground(scene_color);
		}
		return;
	}


	if(imageAnalyzer.isEndScreen(scene_color)) {
		status = NEED_RESET;
		pause(-1);
	}
	auto data = imageAnalyzer.analyzeFrame(scene_color);
	qwopAnalyzer.processData(data);
	qwopAnalyzer.showDebugScreen(scene_color);
	
	
	//waitKey(200);

	if(!isPaused())
		switch(status) {
		case SEARCHING_WINDOW:
			break;
		case NEED_RESET:
			keyPresser.qwopPush("");
			usleep(50000);
			keyPresser.enterText("r");

			status=STARTING1;
			qwopAnalyzer.reset();
			pause(0.5);
			break;
		case STARTING1:

			keyPresser.qwopPush("o");
			pause(0.2);
			status = STARTING2;
			break;
		case STARTING2:
			keyPresser.qwopPush("wo");
			pause(1.4);
			status = STARTING3;
			break;
		case STARTING3:

			keyPresser.qwopPush("");
			status = TRACKING;

			break;
		case TRACKING:

			if(qwopAnalyzer.needStep()) {
				keyPresser.qwopPush("q");
				usleep(200000);
				keyPresser.qwopPush("qp");
				status = PIEDE1;
				pause(1.0);
			}



			break;
		case PIEDE1:
			if(qwopAnalyzer.needStep()) {
				keyPresser.qwopPush("o");
				usleep(200000);
				keyPresser.qwopPush("ow");
				status = TRACKING;
				pause(1.0);
			}
			break;
		}

}
