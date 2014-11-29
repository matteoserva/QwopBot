#include "DecisionMaker.h"
#include <iostream>
DecisionMaker::DecisionMaker()
{

}
void DecisionMaker::endTurn()
{
	if(step > 0) {
		analyzeDecisions(true);
		std::cerr<<"fine turno"<<std::endl;

	}
}


unsigned int DecisionMaker::getStep()
{

	return 0;
}
void DecisionMaker::printDecisionData(DecisionData & data)
{
	std::cerr<<"terra: "<<data.terra<<std::endl;
	std::cerr<<"angolo: "<<data.angolo<<std::endl;
	std::cerr<<"omega: "<<data.omega<<std::endl;
}
void DecisionMaker::analyzeDecisions(bool dead)
{

	if(step == 1) {
		std::cerr <<"compiuto il primo passo ma ignoro"<<std::endl;
		decisioniPrese.clear();
	}
	if(dead) {
		std::cerr <<"utente morto. questi sono i dati dell'ultimo passo"<<decisioniPrese.size()<<std::endl;
		auto lastStep =decisioniPrese.rbegin();

		for(; lastStep != decisioniPrese.rend() && lastStep->second == 0; ++lastStep) {

		}
		if(lastStep == decisioniPrese.rend())
			return;


		printDecisionData(lastStep->first);
		return;
	}
	if(step==2) {
		std::cerr<<"compiuto un altro passo, aspetto per vedere cosa succede"<<std::endl;
	}
	if(step > 2) {
		std::cerr<<"compiuto passo, analizzo..."<<std::endl;
	}
}
unsigned int DecisionMaker::makeDecision(DecisionData& data)
{
	int result;
	float angoloFuturo = data.angolo + data.omega * 0.5;
	if( data.terra && angoloFuturo > 0.2)
		result =  1;
	else
		result = 0;
	

	if(data.piedeLontano)
		result=0;
	decisioniPrese.push_back(std::pair<DecisionData,int>(data,result));

	if(result) {
		std::cerr<<"nuovo passo"<<std::endl;
		step++;
		analyzeDecisions(false);
		//printDecisionData(data);
	}
	return result;
}

void DecisionMaker::newTurn()
{
	std::cerr<<"nuovo turno"<<std::endl;
	decisioniPrese.clear();
	step = 0;
}
