/*
=================
cRadio.h
- Header file for class definition - SPECIFICATION
- Header file for the Player class which is a child of cSprite class
=================
*/
#ifndef _CRADIO_H
#define _cRADIO_H
#include "cSprite.h"

class cRadio : public cSprite
{
private:
	SDL_Point radioVelocity;

public:
	cRadio();
	void update(double deltaTime);
	void setRadioVelocity(SDL_Point radioVel); 
	SDL_Point getRadioVelocity();
};
#endif