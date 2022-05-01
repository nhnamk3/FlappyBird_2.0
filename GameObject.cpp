#include "GameObject.h"
Game::Game()
{}
Game::~Game()
{
	if (!p_bg)			p_bg = NULL;
	if (!p_bird)		p_bird = NULL;
	if (!p_pipe)		p_pipe = NULL;
	if (!p_pauseButton)	p_pauseButton = NULL;
	if (!p_window)		p_window = NULL;
	if (!p_screen)		p_screen = NULL;
	if (!p_text_score)	p_text_score = NULL;
	if (!p_sound_die)	p_sound_die = NULL;
	if (!p_sound_fly)	p_sound_fly = NULL;
	if (!p_sound_hit)	p_sound_hit = NULL;
	if (!p_sound_point)	p_sound_point = NULL;
	if (!p_menu)		p_menu = NULL;
}
bool Game::InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)	return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	p_window = SDL_CreateWindow("Flappy Bird",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (p_window == NULL)	return false;

	p_screen = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);
	if (p_screen == NULL)	return false;

	SDL_SetRenderDrawColor(p_screen, 255, 255, 255, 255);
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) && imgFlags))	return false;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return false;
	}

	if (TTF_Init() == -1)	return false;
	return true;
}
bool Game::InitGame()
{
	if (!p_bg->LoadImg("flappy-bird-assets//sprites//background-day.png", p_screen))	return false;
	p_bg->SetRect(0, 0);

	if (!p_gr->LoadImg("flappy-bird-assets//sprites//base.png", p_screen))	return false;
	p_gr->SetRect(0, 430);

	if (!p_bird->LoadImg("flappy-bird-assets//sprites//bluebird-midflap.png", p_screen))	return false;
	p_bird->SetRect(BIRD_RECT_X_DEFAUT, SCREEN_HEIGHT / 2);

	p_text_score->SetRect(SCREEN_WIDTH / 2, 30);
	SDL_Color color = { 255, 255, 255, 255 };
	p_text_score->SetColor(color);

	for (int i = 0; i < PIPE_NUM; i++) {
		int ranNum = p_pipe->GetRand(0,250);
		Pipe* p_top = (p_pipe + i)->GetPipeTop();
		Pipe* p_bot = (p_pipe + i)->GetPipeBot();
		if (!p_top->LoadImg("flappy-bird-assets//sprites//pipe-green-top.png", p_screen))	return false;
		if (!p_bot->LoadImg("flappy-bird-assets//sprites//pipe-green-bot.png", p_screen))	return false;
		p_top->SetRect(SCREEN_WIDTH * (1 + i), -ranNum);
		p_bot->SetRect(SCREEN_WIDTH * (1 + i), -ranNum + PIPE_DISTANCE + PIPE_HEIGHT);
	}
	if (!p_pauseButton->LoadImg("flappy-bird-assets//sprites//PauseButton.png", p_screen))	return false;
	p_pauseButton->SetRect(SCREEN_WIDTH - p_pauseButton->GetRect().w, 0);

	p_sound_point = Mix_LoadWAV("flappy-bird-assets//audio//point.wav");
	p_sound_hit = Mix_LoadWAV("flappy-bird-assets//audio//hit.wav");
	p_sound_die = Mix_LoadWAV("flappy-bird-assets//audio//die.wav");
	p_sound_fly = Mix_LoadWAV("flappy-bird-assets//audio//wing.wav");
	if (p_sound_die == NULL || p_sound_fly == NULL || p_sound_point == NULL || p_sound_hit == NULL)     return false;

	p_font = TTF_OpenFont("flappy-bird-assets//text//FFFFORWA.ttf", 24);
	if (p_font == NULL)	return false;
	return true;
}
void Game::Render()
{
	SDL_SetRenderDrawColor(p_screen, 255, 255, 255, 255);
	SDL_RenderClear(p_screen);
	//bg_velocity -= 2;
	p_bg->Render(p_screen);
	p_gr->Render(p_screen);
	p_pauseButton->Render(p_screen);
	p_bird->Render(p_screen);
	p_text_score->LoadText(p_font, p_screen);
	p_text_score->Render(p_screen);
	for (int i = 0; i < PIPE_NUM; i++) {
		Pipe* p_top = (p_pipe + i)->GetPipeTop();
		Pipe* p_bot = (p_pipe + i)->GetPipeBot();
		p_top->Render(p_screen);
		p_bot->Render(p_screen);
	}
	SDL_RenderPresent(p_screen);
	SDL_Delay(1000 / 30);
}
void Game::HandleEvent()
{
	SDL_Event events;
	SDL_PollEvent(&events);
	switch (events.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		p_bird->HandleFly(p_sound_fly);
		break;
	case SDL_QUIT:
		isQuit = true;
		break;
	default:
		break;
	}
}
void Game::Update()
{
	p_bird->HandleGravity();
	p_bird->Flapping(p_screen);
	p_text_score->SetText(std::to_string(g_score));
	for (int i = 0; i < PIPE_NUM; i++) {
		(p_pipe + i)->HandleMove(SCREEN_WIDTH);
	}
}
bool Game::GameOver()
{
	for (int i = 0; i < PIPE_NUM; i++) {
		Pipe* p_top = p_pipe->GetPipeTop();
		Pipe* p_bot = p_pipe->GetPipeBot();
		if (p_bird->IsCollision(p_top->GetRect()) || p_bird->IsCollision(p_bot->GetRect())) {
			Mix_PlayChannel(1, p_sound_hit, 0);
			return true;
		}
	}
	return false;
}
Bird* Game::GetBird()
{
	return p_bird;
}
bool Game::GetScore()
{
	Pipe* p_top = p_pipe->GetPipeTop();
	if (p_top->GetRect().x == p_bird->GetRect().x) {
		g_score++;
		return true;
	}
	return false;
}
bool Game::isQuitGame()
{
	return isQuit;
}
bool Game::isPauseGame()
{
	return isPause;
}