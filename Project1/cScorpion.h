/*
=================
cScorpion.h
- Header file for class definition - SPECIFICATION
- Header file for the Player class which is a child of cSprite class
=================
*/
#ifndef _CSCORPION_H
#define _CSCORPION_H
#include "cSprite.h"

class cScorpion : public cSprite
{
private:
	SDL_Point scorpionVelocity;

public:
	cScorpion();
	void update(double deltaTime);		// Scorpion update method
	void setScorpionVelocity(SDL_Point scorpionVel);   // Sets the velocity for the scorpion
	SDL_Point getScorpionVelocity();				 // Gets the scorpion velocity
};
#endif
