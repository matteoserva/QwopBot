#include "StopClock.h"
#include <iostream>
StopClock::StopClock()
	{
		reset();
	}
	float StopClock::secondsSinceLastUpdate()
	{
		Clock::time_point t0 = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(t0 - lastUpdate);
	float result = ms.count()/1000.0;
	//std::cerr <<"sec:"<<result<<std::endl;
	return result;
	}
	
	void StopClock::reset()
	{
		lastUpdate = Clock::now();
	}