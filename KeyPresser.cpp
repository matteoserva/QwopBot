#include "KeyPresser.h"
 #include <iostream>
KeyPresser::KeyPresser()
{
	xdo_instance = xdo_new(NULL);
	q = w = o = p = false;
}
KeyPresser::~KeyPresser()
{
	qwopPush("");
	xdo_free(xdo_instance);
}
void KeyPresser::focus(int x,int y)
{
	xdo_move_mouse(xdo_instance,x,y,0);
	xdo_click_window(xdo_instance,CURRENTWINDOW,1);
}
void KeyPresser::enterText(const char* text)
{
	xdo_enter_text_window(xdo_instance,CURRENTWINDOW,text,12000);
}

void KeyPresser::keyDown(const char *key)
{
	xdo_send_keysequence_window_down(xdo_instance,CURRENTWINDOW,key,12000);
	//	std::cerr<<"keydown "<<key<<std::endl;

	//usleep(10000);
}

void KeyPresser::keyUp(const char *key)
{
	xdo_send_keysequence_window_up(xdo_instance,CURRENTWINDOW,key,12000);
	//usleep(10000);
}
void KeyPresser::qwopPush(const char * keys)
{
	//return;
	bool _q = false;
	bool _w = false;
	bool _o = false;
	bool _p = false;

	const char *keyp =keys;
	while(*keyp != 0) {
		if(*keyp == 'q')
			_q = true;
		if(*keyp == 'w')
			_w = true;
		if(*keyp == 'o')
			_o = true;
		if(*keyp == 'p')
			_p = true;
			keyp++;
	}
		if(q && !_q)
			keyUp("q");
		if(_q && !q)
			keyDown("q");
		if(w && !_w)
			keyUp("w");
		if(_w && !w)
			keyDown("w");
		if(o && !_o)
			keyUp("o");
		if(_o && !o)
			keyDown("o");
		if(p && !_p)
			keyUp("p");
		if(_p && !p)
			keyDown("p");
		
	
	q = _q;
	w = _w;
	o = _o;
	p = _p;
	//std::cerr <<q<<w<<o<<p<<std::endl;
}
