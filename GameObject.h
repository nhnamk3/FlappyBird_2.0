#pragma once
#include "BaseObject.h"
#include "Bird.h"
#include "BackGround.h"
#include "PipeDouble.h"
#include "Ground.h"
#include "TextObject.h"
#include "ButtonObject.h"
#include "Menu.h"
class Game
{
public:
	Game();
	~Game();
	bool InitSDL();
	bool InitGame();
	void Update();
	void Render();
	bool GameOver();
	bool GetScore();
	void HandleEvent();
	Bird* GetBird();
	bool isQuitGame();
	bool isPauseGame();
private:
	bool isQuit = false;
	bool isPause = false;
	BackGround* p_bg = new BackGround;
	Ground* p_gr = new Ground;
	Bird* p_bird = new Bird;
	TextObject* p_text_score = new TextObject;
	PipeDouble* p_pipe = new PipeDouble;
	ButtonObject* p_pauseButton = new ButtonObject;
	Menu* p_menu = new Menu;
	SDL_Window* p_window = NULL;
	SDL_Renderer* p_screen = NULL;
	Mix_Chunk* p_sound_point = NULL;
	Mix_Chunk* p_sound_fly = NULL;
	Mix_Chunk* p_sound_die = NULL;
	Mix_Chunk* p_sound_hit = NULL;
	TTF_Font* p_font = NULL;
};