#include <list>
#include <vector>
struct DecisionData
{
	bool terra;
	float angolo;
	float omega;
	bool piedeLontano;
	float elapsed;
	
	unsigned int getPosition();
	static unsigned int getMaxPosition();
};

class DecisionMaker
{
	std::list< std::pair<DecisionData,int> > decisioniPrese;
	unsigned int step;
	void printDecisionData(DecisionData &);
	unsigned int knowledgePositivi;
	unsigned int knowledgeNegativi;
	std::vector<std::pair<unsigned int,unsigned int> > knowledge;
	float calcolaProbabilita(unsigned int positivi,unsigned int negativi);

public:
	unsigned int makeDecision(DecisionData&);
	void newTurn();
	void endTurn();
	void analyzeDecisions(bool);
	
	
	unsigned int getStep();
	DecisionMaker();
	
};


