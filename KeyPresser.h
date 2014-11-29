extern "C" {
#include "xdo.h"
}
class KeyPresser
{
	xdo_t* xdo_instance;
	bool q;
	bool w;
	bool o;
	bool p;
public:
	KeyPresser();
	~KeyPresser();
	void focus(int x,int y);
	void enterText(const char*);
	int temp;
	void keyDown(const char *key);

	void keyUp(const char *key);
	void qwopPush(const char * keys);
};
