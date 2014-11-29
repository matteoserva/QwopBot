#include "QwopAnalyzer.h"
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
using namespace cv;

const float QwopAnalyzer::distTestaBacino = 121.8;
const float QwopAnalyzer::centroY = 280.0;
const float QwopAnalyzer::testaCom = 87.5;
const float QwopAnalyzer::piedeLontanoThresh = 12000.0;
const int QwopAnalyzer::shoeHeightThresh = 45;

float distance(Point a,Point b)
{
	float dist = (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
	return dist;

}


std::pair<int,float> findNearest(std::vector<cv::Point> lista,cv::Point punto)
{
	std::pair<int,float> result(-1,800.0);

	for(int i = 0; i<lista.size(); i++) {
		float dist = distance(lista[i],punto);
		if(dist < result.second) {
			result.first = i;
			result.second = dist;
		}
	}
	return result;

}

void QwopAnalyzer::processFeet(std::vector<cv::Point> &piedi)
{
	if(piedi.size() == 0)
		return;

	{
		auto dati = findNearest(piedi,body);
		if(dati.first > -1 && dati.second < 800) {
			sign = piedi[dati.first];
			piedi.erase(piedi.begin()+dati.first);
		}

	}
	if(piedi.size() == 0)
		return;



	if(piedi.size() == 2) {
		shoe1 = piedi[0];
		shoe2 = piedi[1];
	}
	if(piedi.size() > 2) {
		if(oddIteration) {
			auto dati = findNearest(piedi,shoe1);

			if(dati.first > -1 ) {
				shoe1 = piedi[dati.first];
				piedi.erase(piedi.begin()+dati.first);
			}

		}

		{
			auto dati = findNearest(piedi,shoe2);

			if(dati.first > -1 ) {
				shoe2 = piedi[dati.first];
				piedi.erase(piedi.begin()+dati.first);
			}

		}
		if(!oddIteration) {
			auto dati = findNearest(piedi,shoe1);

			if(dati.first > -1 ) {
				shoe1 = piedi[dati.first];
				piedi.erase(piedi.begin()+dati.first);
			}

		}

	}



	if(shoe2.x < shoe1.x)
		std::swap(shoe2,shoe1);
}

void QwopAnalyzer::calculateVariables()
{
	terra = shoe1.y > screenHeight - shoeHeightThresh || shoe2.y > screenHeight-shoeHeightThresh;




	{
		float testaCorpo = sqrt(distance(head,body));
		Point bacino1((body.x-head.x) * 120/testaCorpo +head.x,(body.y-head.y) * 120/testaCorpo+head.y);
		float testaRiga = head.x-280.0;
		float b=acos(testaRiga/87.0);
		Point bacino2(head.x-1.4*testaRiga,head.y +fabs(1.4*testaRiga * tan(b)));

		double angolino = asin(8.0/sqrt(distance(head,sign)));
		double angolone = atan2(sign.x-head.x,sign.y-head.y) - angolino;
		Point bacino3(head.x+distTestaBacino*sin(angolone),head.y+distTestaBacino*cos(angolone));
		//circle(screen,bacino3,10,Scalar(0,100,255),7);

		float distUnoDue = distance(bacino1,bacino2);
		float distDueTre = distance(bacino2,bacino3);
		float distUnoTre = distance(bacino1,bacino3);


		int worst = 3;
		if(distUnoTre < distUnoDue && distUnoTre < distDueTre ) {
			//esclude 2
			bacino = Point((bacino1.x + bacino3.x)/2,(bacino1.y + bacino3.y)/2);
		} else if(distDueTre < distUnoDue && distDueTre < distUnoTre) {
			//esclude 1
			bacino = Point((bacino2.x + bacino3.x)/2,(bacino2.y+bacino3.y)/2);
		} else {
			//esclude 3
			bacino = Point((bacino1.x+bacino2.x)/2,(bacino1.y+bacino2.y)/2);
		}

	}
//
	float angoloCOM = atan2(bacino.x-head.x,bacino.y-head.y);
	COM = Point(head.x + 87.5 * sin(angoloCOM),head.y + 87.5*cos(angoloCOM));

	{
		//angoli
		float angoloVecchio = angolo, omegaVecchio = omega;
		float angoloPrevisto = angoloVecchio + elapsed*omegaAvg;
		angolo = -angoloCOM;
		omega = (angolo - angoloVecchio)/(elapsed);


		if(decisionMaker.getStep() > 0 && fabs(angolo -angoloPrevisto>0.5))
			angolo = angoloPrevisto;
		if(fabs(omega-omegaVecchio) > 2.0)
			omega = omegaVecchio;


		angoloAvg = 0.8*angoloVecchio + 0.2 * angolo;
		omegaAvg = 0.8*omegaVecchio + 0.2*omega;
	}

	if(distance(shoe2,bacino)> piedeLontanoThresh)
		piedeLontano = true;
	else
		piedeLontano = false;
	altezza = screenHeight-COM.y;

}


void QwopAnalyzer::showDebugScreen(cv::Mat & screen)
{
	if(terra)
		putText(screen,"terra",Point(250,20),FONT_HERSHEY_COMPLEX_SMALL,1,Scalar::all(255));
	{
		std::stringstream s;
		s<<"angolo: "<<std::fixed<<std::showpos<<angoloAvg;

		putText(screen,s.str().c_str(),Point(0,20),FONT_HERSHEY_COMPLEX_SMALL,1,Scalar::all(255));
	}
	{
		std::stringstream s2;
		s2<<"omega: "<<std::showpos<<std::fixed<<omegaAvg;
		putText(screen,s2.str().c_str(),Point(0,40),FONT_HERSHEY_COMPLEX_SMALL,1,Scalar::all(255));
	}

	{
		std::stringstream s;
		s<<"altezza: "<<altezza;

		putText(screen,s.str().c_str(),Point(0,60),FONT_HERSHEY_COMPLEX_SMALL,1,Scalar::all(255));
	}
	circle(screen,head,5,Scalar(255,50,50),7);
	circle(screen,body,5,Scalar(50,255,50),7);
	/*

		*/

	circle(screen,COM,3,Scalar(255,0,255),7);

	circle(screen,bacino,10,Scalar(0,0,255),7);

	circle(screen,shoe1,5,Scalar(50,200,150),7);
	circle(screen,shoe2,5,Scalar(0,200,200),7);
	//circle(screen,shoe2,80,Scalar(10,255,255),1);
	circle(screen,sign,8,155,7);
	line( screen,bacino,shoe1,Scalar::all(255),2);

	line( screen,shoe2,shoe1,Scalar::all(255),2);
	if(piedeLontano)
		line( screen,shoe2,bacino,cv::Scalar(100,255,100),2);
	else
		line( screen,bacino,shoe2,Scalar::all(255),2);



	Point puntino(bacino.x + sin(angolo)*100.0,bacino.y-cos(angolo)*100.0);
	line( screen,bacino,puntino,Scalar::all(255),2);
	//line( screen,Point(280,20),Point(280,200),Scalar::all(255),2);


	imshow("QWOP",screen);
	waitKey(5);




	//std::cerr<<1.4*testaRiga/cos(b)<<std::endl;
	//line( screen,head,testaCom,Scalar::all(255),2);

}

float QwopAnalyzer::secondsSinceLastUpdate()
{
	Clock::time_point t0 = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(t0 - lastUpdate);
	lastUpdate = t0;
	return ms.count()/1000.0;
}

void QwopAnalyzer::processData(const std::vector<std::pair<char,cv::Point> > &data)
{
	elapsed = secondsSinceLastUpdate();

	auto testa = extractPoints(data,'H');
	auto corpo = extractPoints(data,'B');
	auto piedi = extractPoints(data,'S');
	//Mat screen = Mat::zeros( Size(500,screenHeight), CV_8UC1 );
	if(testa.size() > 0)
		head = testa[0];
	if(corpo.size())
		body = corpo[0];

	processFeet(piedi);


	calculateVariables();



	oddIteration = !oddIteration;
}
void QwopAnalyzer::gestisciMorte()
{
	if(numeroFunzione < 0) {
		numeroFunzione = 0;
		return;
	}
	if(step > 4)
		risultati[numeroFunzione] = risultati[numeroFunzione] + step/4;
	numeroFunzione++;
	if(numeroFunzione > 1)
		numeroFunzione = 0;

	for(int i = 0; i < risultati.size(); i++)
		std::cerr << "risultato "<<i<<":  "<<risultati[i]<<std::endl;

	std::cerr <<"compiuti passi" <<step<<std::endl;
	step = 0;
}
void QwopAnalyzer::reset()
{
	if(!running) {
		running = true;

	} else
		decisionMaker.endTurn();
	omega = 0.2;
	angolo = 0;
	decisionMaker.newTurn();


	gestisciMorte();
}
bool QwopAnalyzer::needStep()
{
	DecisionData data;
	data.terra = terra;
	data.angolo = angoloAvg;
	data.omega = omegaAvg;
	data.piedeLontano = piedeLontano;
	data.elapsed = elapsed;

	if(decisionMaker.makeDecision(data))
		return true;
	return false;


}
std::vector<cv::Point> QwopAnalyzer::extractPoints(const std::vector<std::pair<char,cv::Point> > &data,char type)
{
	std::vector<cv::Point> result;
	for(unsigned int i = 0; i<data.size(); i++) {
		if(data[i].first == type)
			result.push_back(data[i].second);
	}
	return result;
}
QwopAnalyzer::QwopAnalyzer()
{
	lastUpdate = Clock::now();
	screenHeight = 400;
	elapsed = 0.1;
	risultati.resize(2);
	numeroFunzione = -1;
	running = false;
}
