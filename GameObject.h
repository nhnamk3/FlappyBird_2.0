#pragma once
#include "BaseObject.h"
#include "Bird.h"
#include "BackGround.h"
#include "PipeDouble.h"
#include "TextObject.h"
#include "ButtonObject.h"
#include "Menu.h"
#include "ScoreBoard.h"
#include "Medal.h"
#include <fstream>
class Game
{
public:
	Game();
	~Game();
	enum Game_Status {
		newGame, menu, playing, colision, die, quit
	};
	enum Button_Name {
		PLAY, OPTION, QUIT, MUSIC, OK, MENU
	};
	enum Sound_Name {
		WING, POINT, HIT, DIE, CLICK
	};
	enum Text_Name {
		CURRENT_SC, RECENT_SC, HIGH_SC
	};
	enum Medal_Name {
		NO, BRONZE, SILVER, GOLD 
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
	BackGround* p_bg = new BackGround;
	ScoreBoard* p_sb = new ScoreBoard;
	BackGround* p_menu_bg = new BackGround;
	Medal* medal = new Medal[4];
	Bird* p_bird = new Bird;
	TextObject* text = new TextObject[3];
	PipeDouble* p_pipe = new PipeDouble;
	Button* button = new Button[6];
	SDL_Window* p_window = NULL;
	SDL_Renderer* p_screen = NULL;
	Mix_Chunk** sound = new Mix_Chunk*[5];
	Mix_Music* music_bg = NULL;
	TTF_Font* p_font1 = NULL;
	TTF_Font* p_font2 = NULL;
	SDL_Event* events = new SDL_Event;
	Game_Status status_ = menu;
};