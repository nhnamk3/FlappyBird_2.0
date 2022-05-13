#pragma once
#include <fstream>
#include "BaseObject.h"
#include "Bird.h"
#include "PicObject.h"
#include "PipeDouble.h"
#include "TextObject.h"
#include "ButtonObject.h"
#include "Menu.h"
#include "Medal.h"
#include "Tutorial.h"
const int NUM_MEDAL = 4;
const int NUM_BUTTON = 7;
const int NUM_SOUND = 5;
const int NUM_TEXT = 3;
const int NUM_FONT = 3;
class Game
{
public:
	Game();
	~Game();
	enum Game_Status {
		newGame, menu, playing, colision, die, quit, tutor
	};
	enum Button_Name {
		bPLAY, bOPTION, bQUIT, bMUSIC, bOK, bMENU, bTUTOR
	};
	enum Sound_Name {
		sWING, sPOINT, sHIT, sDIE, sCLICK
	};
	enum Text_Name {
		tCURRENT_SC, tFINAL_SC, tHIGH_SC
	};
	enum Medal_Name {
		mNO, mBRONZE, mSILVER, mGOLD 
	};
	enum Font_Name {
		fCURRENT_SC, fFINAL_SC, fTUTOR
	};
	bool InitSDL();
	bool InitGame();
	void Update();
	void Render();
	void Colision();
	void GetScore();
	void HandleEvent();
private:
	bool start = false;
	bool renderBG = false;
	bool isMusic = true;
	bool isChunk = false;
	bool isPlayChanel = true;
	int high_sc;
	PicObject* p_backGround = new PicObject;
	PicObject* p_scoreBoard = new PicObject;
	PicObject* p_menu_bg = new PicObject;
	Tutor* p_tutor = new Tutor;
	Medal* medal = new Medal[NUM_MEDAL];
	Bird* p_bird = new Bird;
	TextObject* text = new TextObject[NUM_TEXT];
	PipeDouble* p_pipe = new PipeDouble;
	Button* button = new Button[NUM_BUTTON];
	SDL_Window* p_window = NULL;
	SDL_Renderer* p_screen = NULL;
	Mix_Chunk** sound = new Mix_Chunk * [NUM_SOUND];
	Mix_Music* music_bg = NULL;
	TTF_Font** font = new TTF_Font * [NUM_FONT];
	SDL_Event* events = new SDL_Event;
	Game_Status status_ = menu;
};