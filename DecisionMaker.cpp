#include "DecisionMaker.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
unsigned int DecisionData::getPosition()
{
	int risultato = 0;
	if(angolo > 0)
		risultato += 2;
	if(terra)
		risultato++;
	return risultato;
}
unsigned int DecisionData::getMaxPosition()
{
	return 2*2;
}

float DecisionMaker::calcolaProbabilita(unsigned int positivi,unsigned int negativi)
{
	if(knowledgePositivi == 0 || knowledgeNegativi == 0)
		return 0.1;
		
	float media = float(knowledgePositivi)/float(knowledgeNegativi+knowledgePositivi);
	
	if(negativi + positivi*20 <50)
		return 0.25;
	
	float mediaKnowledge = float(positivi)/float(negativi+positivi);
	if(mediaKnowledge<=media)
	{
		return sqrt(mediaKnowledge/media) * media;
		
	}
	else
	{
		return 1.0-sqrt((1.0-mediaKnowledge)/(1.0-media))*(1.0-media);
	}
	
		
	
		
		
	
}


DecisionMaker::DecisionMaker()
{
	knowledge.resize(DecisionData::getMaxPosition());
	for(unsigned int i = 0; i<knowledge.size(); i++) {
		knowledge[i].first = 1;
		knowledge[i].second = 0;
	}
	knowledgePositivi=knowledge.size();
	knowledgeNegativi=0;
	srand(time(NULL));
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
		
		for(int i = 0;i<4;i++)
		{
			std::cerr << "i: "<<i<<"   V: "<<knowledge[i].first<<"   S:"<<knowledge[i].second<<
			"   %:"<<(float(knowledge[i].first) / float(knowledge[i].first + knowledge[1].second));
			std::cerr<<"   prob:" 
			<< calcolaProbabilita(knowledge[i].first,knowledge[i].second)<<std::endl;
		}
		std::cerr<<"%: "<<float(knowledgePositivi)/float(knowledgePositivi+knowledgeNegativi);
		auto lastStep =decisioniPrese.rbegin();

		for(; lastStep != decisioniPrese.rend() && lastStep->second == 0; ++lastStep) {

		}
		if(lastStep == decisioniPrese.rend())
			return;
			
		int media = knowledgeNegativi/knowledgePositivi;	
		knowledge[lastStep->first.getPosition()].second += media;
		printDecisionData(lastStep->first);
		return;
	}
	if(step==2) {
		std::cerr<<"compiuto un altro passo, aspetto per vedere cosa succede"<<std::endl;
	}
	if(step > 2) {
		std::cerr<<"compiuto passo, analizzo..."<<std::endl;
		
		
		while(decisioniPrese.begin() != decisioniPrese.end())
		{
			auto firstStep =decisioniPrese.begin();
			int risultato = firstStep->second;
			int numero = firstStep->first.getPosition();
			decisioniPrese.pop_front();
			if(risultato)
			{
				knowledge[numero].first++;
				knowledgePositivi++;
				break;
			}
			else
			{
				knowledgeNegativi++;
				knowledge[numero].second++;
			}
			
		} 
		
		
		
	}


}
unsigned int DecisionMaker::makeDecision(DecisionData& data)
{
	/*int result;
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
	return result;*/
	int result;
	auto dati = knowledge[data.getPosition()];
	
	float prob= calcolaProbabilita(dati.first,dati.second);
	if(rand()%1000 <prob*1000.0)
		result = 1;
	else
		result = 0;


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
