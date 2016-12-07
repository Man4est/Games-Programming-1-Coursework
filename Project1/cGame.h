#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "2DGame.h"

using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	bool respawn = false;

	double getElapsedSeconds();
	static cGame* getInstance();



private:

	static cGame* pInstance;
	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;
	bool loop;
	bool fileAvailable;

	// Sprites for displaying background, player and game objects
	cSprite spriteBkgd;
	cSprite spriteBkgdLevel;
	cPlayer thePlayer;
	cScorpion theScorpion;
	cCrate theCrate;
	cRadio theRadio;
	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> textName;
	vector <cPlayer*> thePlayers;
	vector<cScorpion*> theScorpions;
	vector<cCrate*> theCrates;
	vector<cRadio*> theRadios;

	vector<LPCSTR> texturesToUse;
	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextNames;
	vector<LPCSTR> gameTextList;
	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;
	// Create vector array of button textures
	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;

	// Define the elements and there position in/on the array/map
	cSprite dragTile;
	SDL_Point theTileClicked;
	SDL_Point mapTileClicked;
	int renderWidth;
	int renderHeight;
	int score;
	cFileHandler theFile;
	string strScore;
	gameState theGameState;
	btnTypes theBtnType;
	SDL_Rect pos;
	FPoint scale;
	SDL_Rect aRect;
	SDL_Color aColour;
	cTexture* tempTextTexture;
	SDL_Point theAreaClicked;

};

#endif
