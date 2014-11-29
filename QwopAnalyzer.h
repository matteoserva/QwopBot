#include <opencv/cv.h>
#include <vector>
#include <chrono>
#include "DecisionMaker.h"
class QwopAnalyzer
{
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds milliseconds;
	Clock::time_point lastUpdate;
	
	float secondsSinceLastUpdate();
	
	
	std::vector<cv::Point> extractPoints(const std::vector<std::pair<char,cv::Point> > &,char);
	
	cv::Point head;
	cv::Point body;
	cv::Point sign;
	cv::Point shoe1;
	cv::Point shoe2;
	cv::Point bacino;
	cv::Point COM;
	
	bool oddIteration;
	float angolo;
	float omega;
	float angoloAvg;
	float omegaAvg;
	unsigned int step;
	bool piedeLontano;
	bool terra;
	unsigned int screenHeight;
	double elapsed;
	bool running;
	int altezza;

	void processFeet(std::vector<cv::Point> &);
	void calculateVariables();
	void gestisciMorte();
	std::vector<unsigned int> risultati;
	int numeroFunzione;
	DecisionMaker decisionMaker;
	static const float distTestaBacino;
	static const float centroY;
	static const float testaCom ;
	static const float piedeLontanoThresh ;
	static const int shoeHeightThresh;


public:
	void processData(const std::vector<std::pair<char,cv::Point> > &);
	QwopAnalyzer();
	void showDebugScreen(cv::Mat &);

	bool needStep();
	void reset();

};
