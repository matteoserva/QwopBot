#include <list>
struct DecisionData
{
	bool terra;
	float angolo;
	float omega;
	bool piedeLontano;
	float elapsed;
};

class DecisionMaker
{
	std::list< std::pair<DecisionData,int> > decisioniPrese;
	unsigned int step;
	void printDecisionData(DecisionData &);
public:
	unsigned int makeDecision(DecisionData&);
	void newTurn();
	void endTurn();
	void analyzeDecisions(bool);
	
	unsigned int getStep();
	DecisionMaker();
	
};


