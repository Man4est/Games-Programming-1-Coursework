/*
=================
cPlayer.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayer.h"


/*
=================================================================
Defualt Constructor
=================================================================
*/
cPlayer::cPlayer() : cSprite()
{
	this->playerVelocity = { 0, 0 };

}


/*
=================================================================
Update the sprite position
=================================================================
*/

void cPlayer::update(double deltaTime)
{

	FPoint direction = { 0, 0 };
	direction.X = (sin(this->getSpriteRotAngle()*PI / 180));
	direction.Y = -(cos(this->getSpriteRotAngle()*PI / 180));

	direction.X *= this->getSpriteTranslation().x;
	direction.Y *= this->getSpriteTranslation().y;

	this->playerVelocity.x = this->playerVelocity.x + direction.X;
	this->playerVelocity.y = this->playerVelocity.y + direction.Y;

	SDL_Rect currentSpritePos = this->getSpritePos();
	currentSpritePos.x += this->playerVelocity.x * deltaTime;
	currentSpritePos.y += this->playerVelocity.y * deltaTime;

	this->setSpritePos({ currentSpritePos.x, currentSpritePos.y });
	this->playerVelocity.x *= 1;
	this->playerVelocity.y *= 1;

	this->setBoundingRect(this->getSpritePos());
	cout << "Player position - x: " << this->getSpritePos().x << " y: " << this->getSpritePos().y << " deltaTime: " << deltaTime << ' ' << this->playerVelocity.x * deltaTime << endl;
}

/*
=================================================================
Sets the velocity for the player
=================================================================
*/
void cPlayer::setPlayerVelocity(SDL_Point playerVel)
{
	playerVelocity = playerVel;
}
/*
=================================================================
Gets the player velocity
=================================================================
*/
SDL_Point cPlayer::getPlayerVelocity()
{
	return playerVelocity;
}


