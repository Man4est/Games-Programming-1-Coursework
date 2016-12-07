/*
=================
cCrate.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cCrate.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cCrate::cCrate() : cSprite()
{
	this->crateVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cCrate::update(double deltaTime)
{

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime;
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
//	cout << "Crate position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
  Sets the velocity for the Crate
=================================================================
*/
void cCrate::setCrateVelocity(SDL_Point CrateVel)
{
	crateVelocity = CrateVel;
}
/*
=================================================================
  Gets the Crate velocity
=================================================================
*/
SDL_Point cCrate::getCrateVelocity()
{
	return crateVelocity;
}
