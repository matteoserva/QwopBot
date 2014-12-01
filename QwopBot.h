#include <chrono>
#include <ScreenGrabber.h>
#include "QwopAnalyzer.h"
#include "KeyPresser.h"
#include "ImageAnalyzer.h"
#include "StopClock.h"
class QwopBot
{
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds milliseconds;
	ScreenGrabber screenGrabber;
ImageAnalyzer imageAnalyzer;
	StopClock clock;


	QwopAnalyzer qwopAnalyzer;
	KeyPresser keyPresser;

	float pauseTime;
	Clock::time_point clockStart;

public:
	enum {SEARCHING_WINDOW,TRACKING,NEED_RESET,STARTING1,STARTING2,STARTING3,PIEDE1} status;
	void pause(float seconds);
	bool isPaused();
	QwopBot();
	~QwopBot();
	void step();

};