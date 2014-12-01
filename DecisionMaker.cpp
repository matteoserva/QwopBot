#include "DecisionMaker.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
unsigned int DecisionMaker::getStatePosition(DecisionData & dato)
{
	int risultato = 0;
	/*if(dato.omega > 1.0)
		risultato +=8;*/
	if(dato.piedeLontano)
		risultato += 4;
	if(dato.angolo > 0)
		risultato += 2;
	if(dato.terra)
		risultato++;
	return risultato;
}
unsigned int DecisionMaker::getStatesSize()
{
	return 2*2*2;
}
unsigned int DecisionMaker::getActionsSize()
{
	return 2;
}

DecisionMaker::DecisionMaker()
{
	Q = new float[getStatesSize()*getActionsSize()];
	for(unsigned int i = 0; i<getStatesSize()*getActionsSize(); i++)
		Q[i] = 0.0;
	srand(time(NULL));
}
DecisionMaker::~DecisionMaker()
{
	delete [] Q;
}
void DecisionMaker::printQ()
{
	for(unsigned int i = 0; i<getStatesSize(); i++) {
		std::cerr << i<<")  ";
		for(unsigned int j = 0; j<getActionsSize(); j++) {
			std::cerr<<Q[i*getActionsSize()+j]<<"  ";
		}
		std::cerr<<std::endl;

	}
}
void DecisionMaker::endTurn()
{
	if(step==0 || episode.size() < 2)
		return;

	auto it = episode.rbegin();
	unsigned int newState = it->first;
	float trueReward = -1.0 * step;
	++it;
	for(; it!=episode.rend(); ++it) {
		unsigned int state = it->first;
		unsigned int action = it->second;
		float rew = -1;
		if(action >0) {
			rew = trueReward;
			if(trueReward < -0.5)
			trueReward = step;
			else if(trueReward > 0.5)
				trueReward = 0;
		}
		reward(state,action,newState,rew);

		newState = state;
	}


	printQ();
}
float DecisionMaker::getMaxQ(unsigned int state)
{
	float *baseQ = &Q[state*getActionsSize()];
	float maxQ = baseQ[0];
	for (unsigned int i = 1; i<getActionsSize(); i++)
		maxQ = std::max(maxQ,baseQ[i]);
	return maxQ;
}
void DecisionMaker::reward(unsigned int state,unsigned int action,unsigned int newState,float reward)
{
	float gamma = 0.2;
	float rate = 0.2;

	float maxQ = getMaxQ(newState);

	float *baseQ = &Q[state*getActionsSize() + action];

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
	if(episode.size()>0 && episode.back().first == state && rand()%100 < 3 ) {

		result = episode.back().second;
		episode.pop_back();
	}

	else {

		float differenza = Q[state*getActionsSize() +1] - Q[state*getActionsSize()];

		if(differenza > 0)
			result = 1;
		else
			result = 0;

		float probInversione = 0.02 * 0.1/(0.1 + fabs(differenza) );
		if(rand()%1000 < 1000.0*probInversione) {
			result = rand()%getActionsSize();

		}
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
