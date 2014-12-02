#include "DecisionMaker.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
unsigned int DecisionMaker::getStatePosition(DecisionData & dato)
{
	int risultato = 0;
	if(dato.terra)
		risultato++;

	risultato<<=2;
	if(dato.angolo >-1.0)
		risultato++;
	if(dato.angolo>0.0)
		risultato++;
	if(dato.angolo>1.0)
		risultato++;
risultato<<=1;
	if(dato.piedeLontano)
		risultato++;

	return risultato;
}
unsigned int DecisionMaker::getStatesSize()
{
	return 2*4*2;
}
unsigned int DecisionMaker::getActionsSize()
{
	return 2;
}

DecisionMaker::DecisionMaker()
{
	Qdata = new float[getStatesSize()*getActionsSize()];
	for(unsigned int i = 0; i<getStatesSize()*getActionsSize(); i++)
		Qdata[i] = 0.0;
	srand(time(NULL));
}
DecisionMaker::~DecisionMaker()
{
	delete [] Qdata;
}
void DecisionMaker::printQ()
{
	//std::cerr.precision(4);
	
	for(unsigned int i = 0; i<getStatesSize(); i++) {
		std::cerr << i<<")  ";

		for(unsigned int j = 0; j<getActionsSize(); j++) {
			std::cerr<<j<<":"<<Q(i,j)<<"\t";
		}
		std::cerr<<std::endl;

	}
}

float & DecisionMaker::Q(unsigned int s,unsigned int a)
{
	return Qdata[s*getActionsSize() + a];
}
void DecisionMaker::endTurn()
{
	if( episode.size() < 2)
		return;

	auto it = episode.rbegin();
	unsigned int newState = it->first;


	int revStep = 0;
	for(; it!=episode.rend(); ++it) {
		unsigned int state = it->first;
		unsigned int action = it->second;
		if(action >0)
			revStep++;

		float rew = 0;
		if(revStep == 0)
			rew = -0.1;
		else if(action > 0 && revStep == 1)
			rew = -1.0* step;
		else if(action > 0 && revStep > 2)
			rew = 1.0 + 0.1*step;

		reward(state,action,newState,rew);

		newState = state;
	}



	printQ();
}
float DecisionMaker::getMaxQ(unsigned int state)
{
	float *baseQ = &Qdata[state*getActionsSize()];
	float maxQ = baseQ[0];
	for (unsigned int i = 1; i<getActionsSize(); i++)
		maxQ = std::max(maxQ,baseQ[i]);
	return maxQ;
}
void DecisionMaker::reward(unsigned int state,unsigned int action,unsigned int newState,float reward)
{
	std::cerr <<"reward: "<<reward<<"\t";
	float gamma = 0.6;
	float rate = 0.5;

	float maxQ = getMaxQ(newState);

	float *baseQ = &Qdata[state*getActionsSize() + action];
	std::cerr<<"Q: "<<*baseQ<<" reward:"<<reward<<"  maxQ"<<maxQ<<std::endl;

	*baseQ = *baseQ + rate*( reward + gamma * maxQ  -*baseQ);
}
unsigned int DecisionMaker::getStep()
{
	return step;

}
void DecisionMaker::printDecisionData(DecisionData & data)
{
	std::cerr<<"terra: "<<data.terra<<std::endl;
	std::cerr<<"angolo: "<<data.angolo<<std::endl;
	std::cerr<<"omega: "<<data.omega<<std::endl;
}


unsigned int DecisionMaker::makeDecision(DecisionData& data)
{
	unsigned int state = getStatePosition(data);
	unsigned int result = 0;
	if(episode.size()>0 && episode.back().first == state && rand()%100 >3) {

		result = episode.back().second;
		episode.pop_back();
	}

	else {

		float differenza = Qdata[state*getActionsSize() +1] - Qdata[state*getActionsSize()];

		if(differenza > 0)
			result = 1;
		else
			result = 0;

		float probInversione = 0.2 * 0.1/(0.1 + fabs(differenza) );
		if(rand()%1000 < 1000.0*probInversione) {
			result = rand()%getActionsSize();

		}
		std::cerr<<"stato: "<<state<<"  R: "<<result<<"      disobb: "<<probInversione<<std::endl;
	}

	if(result)
		step++;

	episode.push_back(std::pair<unsigned int,unsigned int>(state,result));
	return result;
}

void DecisionMaker::newTurn()
{
	std::cerr<<"nuovo turno"<<std::endl;
	episode.clear();
	step = 0;
}
