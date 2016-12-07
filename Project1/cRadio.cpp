/*
=================
cRadio.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRadio.h"

/*
=================================================================
Defualt Constructor
=================================================================
*/
cRadio::cRadio() : cSprite()
{
	this->radioVelocity = { 0, 0 };
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cRadio::update(double deltaTime)
{

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->getSpriteTranslation().x * deltaTime;
	currentSpritePos.y += this->getSpriteTranslation().y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	//cout << "Radio position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << endl;
	this->setBoundingRect(this->getSpritePos());
}
/*
=================================================================
  Sets the velocity for the Radio
=================================================================
*/
void cRadio::setRadioVelocity(SDL_Point RadioVel)
{
	radioVelocity = RadioVel;
}
/*
=================================================================
  Gets the Radio velocity
=================================================================
*/
SDL_Point cRadio::getRadioVelocity()
{
	return radioVelocity;
}
