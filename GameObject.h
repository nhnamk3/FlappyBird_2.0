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
const int NUM_TEXT = 5;
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
		tCURRENT_SC, tFINAL_SC, tHIGH_SC, tMess
	};
	enum Medal_Name {
		mNO, mBRONZE, mSILVER, mGOLD 
	};
	enum Font_Name {
		fCURRENT_SC, fFINAL_SC, fTUTOR, fMESS
	};
	bool InitSDL();
	bool InitGame();
	void Update();
	void Render();
	void Colision();
	void GetScore();
	void HandleEvent();
private:
	double time = 0;
	bool start = false; // Kiem tra game bat dau chua
	bool renderBG = false; //Kiem tra tranh phai ve background nhieu lan
	bool isMusic = true; //Kiem tra de choi nhac background 1 lan
	bool isChunk = false; //Kiem tra de tranh keu "HIT" va "DIE" lien tuc khi chet
	bool isPlayChanel = true; //Kiem tra de keu "HIT" 1 lan khi va cham lien tuc
	bool showMess = false; //Hien thi message cap nhat option
	int high_sc;
	PicObject* p_backGround = new PicObject;
	PicObject* p_scoreBoard = new PicObject;
	PicObject* p_menu_bg = new PicObject;
	Tutor* p_tutor = new Tutor;
	Bird* p_bird = new Bird;
	PipeDouble* p_pipe = new PipeDouble;
	SDL_Event* events = new SDL_Event;
	SDL_Window* p_window = NULL;
	SDL_Renderer* p_screen = NULL;
	Mix_Music* music_bg = NULL;
	TextObject* text = new TextObject[NUM_TEXT];
	Medal* medal = new Medal[NUM_MEDAL];
	Button* button = new Button[NUM_BUTTON];
	TTF_Font** font = new TTF_Font * [NUM_FONT];
	Mix_Chunk** sound = new Mix_Chunk * [NUM_SOUND];
	Game_Status status_ = menu;
};