/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();

/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{
}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	//initializes texture, font and sound manages and sets the score and area clicked to zero
	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();
	score = 0;
	theAreaClicked = { 0, 0 };
	// Store the game textures
	textureName = { "theCrate", "thePlayer", "theSnake", "theScorpion", "theRadio","tile6","theBackground","theMenuBkg", };
	texturesToUse = { "Images/Objects/crate (2).png", "Images/Objects/randy.png", "Images/Objects/snake.png", "Images/Objects/scorpion.png", "Images/Objects/radio.png", "Images/Tiles/6.png", "Images/Bkg/background1.png", "Images/Bkg/menubackground.png" };
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	/*
	tempTextTexture = theTextureMgr->getTexture("theCrate");
	aRect = { 0, 0, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	aColour = { 228, 213, 238, 255 };
	*/
	// Store the menu object textures
	btnNameList = { "exit_btn", "instructions_btn", "load_btn", "menu_btn", "play_btn", "save_btn", "settings_btn"};
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png", "Images/Buttons/button_load.png", "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png", "Images/Buttons/button_save.png", "Images/Buttons/button_settings.png"};
	btnPos = { { 400, 375 }, { 400, 300 }, { 400, 300 }, { 500, 500 }, { 400, 300 }, { 740, 500 }, { 400, 300 } };
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = MENU;
	theBtnType = EXIT;
	// Create textures for Game Dialogue (text)
	fontList = { "Xball", "same" };
	fontsToUse = { "Fonts/Xball.ttf", "Fonts/Xball.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 48);
	}

	// Create text Textures
	gameTextNames = {"TitleTxt", "CreateTxt", "Score:", "ScoreTxt", "DragDropTxt", "ThanksTxt", "SeeYouTxt", "Gameover", "Win"};
	gameTextList = {"Macho Man's Slim Jim Adventure", "Grab crate and radio with arrow keys","Score:", "Score:", "Get the Cargo", "Thanks for Playing" ,"On to Wrestlemania", "Game Over", "You Win"};

	for (int text = 0; text < gameTextNames.size(); text++)
	{
		theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("Xball")->createTextTexture(theRenderer, gameTextList[text], SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 }));
	}

	// Load game sounds
	soundList = { "theme", "click", "ohyeh" };
	soundTypes = { MUSIC, SFX, SFX };
	soundsToUse = { "Audio/Theme/desert_theme.wav", "Audio/SFX/ClickOn.wav", "Audio/SFX/OYeh.wav" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}
	theSoundMgr->getSnd("theme")->play(-1);

	//Render the background
	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theMenuBkg"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theMenuBkg")->getTWidth(), theTextureMgr->getTexture("theMenuBkg")->getTHeight());

	spriteBkgdLevel.setSpritePos({ 0, 0 });
	spriteBkgdLevel.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgdLevel.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	//To Render the player and game objects
	thePlayers.push_back(new cPlayer);
	thePlayers[0]->setSpritePos({ 100, 700 });
	thePlayers[0]->setTexture(theTextureMgr->getTexture("thePlayer"));
	thePlayers[0]->setSpriteDimensions(theTextureMgr->getTexture("thePlayer")->getTWidth(), theTextureMgr->getTexture("thePlayer")->getTHeight());
	thePlayers[0]->setPlayerVelocity({ 0, 0 });

	theScorpions.push_back(new cScorpion);
	theScorpions[0]->setSpritePos({ 400, 700 });
	theScorpions[0]->setTexture(theTextureMgr->getTexture("theScorpion"));
	theScorpions[0]->setSpriteDimensions(theTextureMgr->getTexture("theScorpion")->getTWidth(), theTextureMgr->getTexture("theScorpion")->getTHeight());
	theScorpions[0]->setScorpionVelocity({ 0, 0 });

	theCrates.push_back(new cCrate);
	theCrates[0]->setSpritePos({ 200, 700 });
	theCrates[0]->setTexture(theTextureMgr->getTexture("theCrate"));
	theCrates[0]->setSpriteDimensions(theTextureMgr->getTexture("theCrate")->getTWidth(), theTextureMgr->getTexture("theCrate")->getTHeight());
	theCrates[0]->setCrateVelocity({ 0, 0 });


	theRadios.push_back(new cRadio);
	theRadios[0]->setSpritePos({ 900, 700 });
	theRadios[0]->setTexture(theTextureMgr->getTexture("theRadio"));
	theRadios[0]->setSpriteDimensions(theTextureMgr->getTexture("theRadio")->getTWidth(), theTextureMgr->getTexture("theRadio")->getTHeight());
	theRadios[0]->setRadioVelocity({ 0, 0 });


}


void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	//Game states
	switch (theGameState)
	{
		//Main Menu state
	case MENU:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		//Render the screen text
		tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("CreateTxt");
		pos = { 10, 60, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		// Render Buttons
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 400, 375 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	// Main level state
	case PLAYING:
	{

		spriteBkgdLevel.render(theRenderer, NULL, NULL, spriteBkgdLevel.getSpriteScale());
		//Render the player and objects
		thePlayers[0]->render(theRenderer, &thePlayers[0]->getSpriteDimensions(), &thePlayers[0]->getSpritePos(), thePlayers[0]->getSpriteRotAngle(), &thePlayers[0]->getSpriteCentre(), thePlayers[0]->getSpriteScale());
		if (!theScorpions.empty())
			theScorpions[0]->render(theRenderer, &theScorpions[0]->getSpriteDimensions(), &theScorpions[0]->getSpritePos(), theScorpions[0]->getSpriteRotAngle(), &theScorpions[0]->getSpriteCentre(), theScorpions[0]->getSpriteScale());
		theCrates[0]->render(theRenderer, &theCrates[0]->getSpriteDimensions(), &theCrates[0]->getSpritePos(), theCrates[0]->getSpriteRotAngle(), &theCrates[0]->getSpriteCentre(), theCrates[0]->getSpriteScale());
		theRadios[0]->render(theRenderer, &theRadios[0]->getSpriteDimensions(), &theRadios[0]->getSpritePos(), theRadios[0]->getSpriteRotAngle(), &theRadios[0]->getSpriteCentre(), theRadios[0]->getSpriteScale());

		//score render
		
		theTextureMgr->addTexture("ScoreTxt", theFontMgr->getFont("Xball")->createTextTexture(theRenderer, strScore.c_str(), SOLID, { 228, 213, 238, 255 }, { 0, 0, 0, 0 }));
		tempTextTexture = theTextureMgr->getTexture("ScoreTxt");
		pos = { 500, 80 , tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);



		//Objective and buttons
		tempTextTexture = theTextureMgr->getTexture("DragDropTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 760, 50 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	// End game state if quit is clicked
	case END:
	{
		//Background
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		//Game text
		tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("ThanksTxt");
		pos = { 300, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("SeeYouTxt");
		pos = { 350, 150, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		// buttons
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	// Game over state is player collides with a scorpion
	case GAMEOVER:
	{
		//background
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		//text
		tempTextTexture = theTextureMgr->getTexture("Gameover");
		pos = { 400, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);


		tempTextTexture = theTextureMgr->getTexture("ScoreTxt");
		pos = { 100, 50, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//buttons
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	//Win screen state if player reaches the radio
	case WIN:
	{
		//background
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		//text
		tempTextTexture = theTextureMgr->getTexture("Win");
		pos = { 400, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		tempTextTexture = theTextureMgr->getTexture("ScoreTxt");
		pos = { 100, 50, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		//buttons
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	}
	break;
	case QUIT:
	{
		loop = false;
	}
	break;
	default:
		break;
	}
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	gameState oldGameState = theGameState;

	// CHeck Button clicked and change state
	if (theGameState == MENU || theGameState == END || theGameState == GAMEOVER || theGameState == WIN)
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, QUIT, theAreaClicked);
	}
	else
	{
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, END, theAreaClicked);
	}
	theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);

	theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, MENU, theAreaClicked);


	//checks if there has been a change in gamestates
	if (theGameState != oldGameState)
	{
		
	//resets the playing state when its set
		if (theGameState == PLAYING)
		{

			score = 0;
			thePlayers[0]->setSpritePos({ 100, 700 });
			thePlayers[0]->setPlayerVelocity({ 0, 0 });


			theCrates[0]->setSpritePos({ 200, 700 });
			theCrates[0]->setCrateVelocity({ 0, 0 });


			theRadios[0]->setSpritePos({ 900, 700 });
			theRadios[0]->setRadioVelocity({ 0, 0 });

			strScore = gameTextList[2] + to_string(score);
			//the old score is deleted and gets replaced by the new one in the vector.
			theTextureMgr->deleteTexture("ScoreTxt");

		}
		theAreaClicked = { 0, 0 };
	}
	
	if (theGameState == PLAYING)
	{
		thePlayers[0]->update(deltaTime);
		//creates the vectors for the collision check
		vector<cScorpion*>::iterator scorpionIterator = theScorpions.begin();
		while (scorpionIterator != theScorpions.end())
		{
			if ((*scorpionIterator)->isActive() == false)
			{
				scorpionIterator = theScorpions.erase(scorpionIterator);
			}
			else
			{
				(*scorpionIterator)->update(deltaTime);
				++scorpionIterator;
			}
		}

		vector<cCrate*>::iterator crateIterator = theCrates.begin();
		while (crateIterator != theCrates.end())
		{
			if ((*crateIterator)->isActive() == false)
			{
				crateIterator = theCrates.erase(crateIterator);
			}
			else
			{
				(*crateIterator)->update(deltaTime);
				++crateIterator;
			}
		}
		vector<cRadio*>::iterator radioIterator = theRadios.begin();
		while (radioIterator != theRadios.end())
		{
			if ((*radioIterator)->isActive() == false)
			{
				radioIterator = theRadios.erase(radioIterator);
			}
			else
			{
				(*radioIterator)->update(deltaTime);
				++radioIterator;
			}
		}
		//checks for collisions between the scorpion and player
		for (vector<cPlayer*>::iterator playerIterartor = thePlayers.begin(); playerIterartor != thePlayers.end(); ++playerIterartor)
		{

			for (vector<cScorpion*>::iterator scorpionIterator = theScorpions.begin(); scorpionIterator != theScorpions.end(); ++scorpionIterator)
			{//if a collision is found it switches the game state accordingly
				if ((*scorpionIterator)->collidedWith(&(*scorpionIterator)->getBoundingRect(), &thePlayers[0]->getBoundingRect()))

				{
					theGameState = GAMEOVER;

				}
				//checks for collisions between the crate and the player
				for (vector<cCrate*>::iterator crateIterator = theCrates.begin(); crateIterator != theCrates.end(); ++crateIterator)
				{
					if ((*crateIterator)->collidedWith(&(*crateIterator)->getBoundingRect(), &thePlayers[0]->getBoundingRect()))

					{
						
						//this updates the score,  turns it into a string and concatenates it to the text in the gameTextList.
						score++;
						strScore = gameTextList[2] + to_string(score);
						//the old score is deleted and gets replaced by the new one in the vector.
						theTextureMgr->deleteTexture("ScoreTxt");
						theCrates[0]->setSpritePos({ 10000, 100000 });
						
					}

				}
				//checks for collisions between the radio and the player
				for (vector<cRadio*>::iterator radioIterator = theRadios.begin(); radioIterator != theRadios.end(); ++radioIterator)
				{//if a collision is found it switches the game state accordingly
					if ((*radioIterator)->collidedWith(&(*radioIterator)->getBoundingRect(), &thePlayers[0]->getBoundingRect()))

					{
						theGameState = WIN;
					}

				}
				//Presents us with the ground
				if ((thePlayers[0]->getSpritePos().y > 700))
				{
					thePlayers[0]->setSpriteTranslation({ 0,0 });
					thePlayers[0]->setSpritePos({ thePlayers[0]->getSpritePos().x, 700 });
				}
				//Simulates gravity 
				if ((thePlayers[0]->getSpritePos().y < 700))
				{
					int ytrans = thePlayers[0]->getSpriteTranslation().y;
					thePlayers[0]->setSpriteTranslation({ thePlayers[0]->getSpriteTranslation().x, ytrans - 1 });
				}

				thePlayers[0]->update(deltaTime);
			}
		}
	}
}


bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					theAreaClicked = { event.motion.x, event.motion.y };
				theSoundMgr->getSnd("click")->play(0);			
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{

				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			{
				
			}
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					theLoop = false;
					break;
					//down movenment
				case SDLK_DOWN:
				{
					{
						thePlayers[0]->setSpriteTranslation({ -10, -10 });
					}
						
				}
				break;
				// up movenment
				case SDLK_UP:
				{
					thePlayers[0]->setSpriteTranslation({ 10, 10 });

				}
				break;
				// right movenment
				case SDLK_RIGHT:
				{
					{
						thePlayers[0]->setPlayerVelocity({ 100, 0 });
					}
				}
				break;

				case SDLK_LEFT:		
					//left movenment

				{
					{
						thePlayers[0]->setPlayerVelocity({ -10 , 0 });

					}
				}
				break;
				case SDLK_SPACE:
				{
				}
				break;
				default:
					break;
				}

			default:
				break;
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

