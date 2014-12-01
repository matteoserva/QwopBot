#include <list>
#include <vector>
struct DecisionData {
	bool terra;
	float angolo;
	float omega;
	bool piedeLontano;
	float elapsed;


};

class DecisionMaker
{
	unsigned int getStatePosition(DecisionData&);
	static unsigned int getStatesSize();
	static unsigned int getActionsSize();
	unsigned int step;
	void printDecisionData(DecisionData & data);
	
	float *Q;
	std::list<std::pair<unsigned int, unsigned int> > episode;
	void printQ();
	
	float getMaxQ(unsigned int);
	void reward(unsigned int,unsigned int,unsigned int,float);
public:
	unsigned int makeDecision(DecisionData&);
	void newTurn();
	void endTurn();
	

	unsigned int getStep();
	DecisionMaker();
	~DecisionMaker();

};
