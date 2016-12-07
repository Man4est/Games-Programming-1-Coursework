/*
=================
cScorpion.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cScorpion.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cScorpion::cScorpion() : cSprite()
{
	this->scorpionVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cScorpion::update(double deltaTime)
{


	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime;
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	//cout << "Scorpion position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
  Sets the velocity for the Scorpion
=================================================================
*/
void cScorpion::setScorpionVelocity(SDL_Point ScorpionVel)
{
	scorpionVelocity = ScorpionVel;
}
/*
=================================================================
  Gets the Scorpion velocity
=================================================================
*/
SDL_Point cScorpion::getScorpionVelocity()
{
	return scorpionVelocity;
}
