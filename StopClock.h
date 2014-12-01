#include <chrono>
class StopClock
{
	

	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds milliseconds;
	Clock::time_point lastUpdate;
	public:
	StopClock();
	float secondsSinceLastUpdate();
	
	void reset();
};