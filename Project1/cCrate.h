/*
=================
cCrate.h
- Header file for class definition - SPECIFICATION
- Header file for the Player class which is a child of cSprite class
=================
*/
#ifndef _CCRATE_H
#define _CCRATE_H
#include "cSprite.h"

class cCrate : public cSprite
{
private:
	SDL_Point crateVelocity;

public:
	cCrate();
	void update(double deltaTime);		// Crate update method
	void setCrateVelocity(SDL_Point cratevel);   // Sets the velocity for the crate
	SDL_Point getCrateVelocity();				 // Gets the crate velocity
};
#endif