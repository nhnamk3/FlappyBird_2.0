#include "GameObject.h"
Game::Game()
{
	std::ifstream file("HighScore.txt");
	file >> high_sc;
	file.close();
}
Game::~Game()
{
	if (!p_bg)			delete p_bg;
	if (!p_bird)		delete p_bird;
	if (!p_pipe)		delete p_pipe;
	if (!p_window)		SDL_DestroyWindow(p_window);
	if (!p_screen)		SDL_DestroyRenderer(p_screen);
	if (!p_menu_bg)		delete p_menu_bg;
	if (!events)		delete events;
	if (!music_bg)		Mix_FreeMusic(music_bg);
	if (!p_sb)			delete p_sb;
	if (!text)			delete[] text;
	if (!button)		delete[] button;
	if (!medal)			delete[] medal;
	if (!p_font1)		TTF_CloseFont(p_font1);
	if (!p_font2)		TTF_CloseFont(p_font2);
	for (int i = 0; i < 4; i++) {
		if (!sound[i])	Mix_FreeChunk(sound[i]);
	}
	SDL_Quit();
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
	g_score = 0;
	start = false;
	renderBG = false;
	isMusic = true;
	isChunk = false;
	isPlayChanel = true;
	if (rand() % 2) {
		if (!p_bg->LoadImg("flappy-bird-assets//sprites//background-day.png", p_screen))		return false;
	}
	else {
		if (!p_bg->LoadImg("flappy-bird-assets//sprites//background-night.png", p_screen))		return false;
	}
	if (!p_sb->LoadImg("flappy-bird-assets//sprites//score_board.png", p_screen))			return false;
	if (!p_bird->LoadImg("flappy-bird-assets//sprites//bluebird-midflap.png", p_screen))	return false;
	if (!p_menu_bg->LoadImg("flappy-bird-assets//sprites//menu_bg.png", p_screen))			return false;

	p_bg->SetRect(0, 0);
	p_sb->SetRect(0, 0);
	p_bird->SetRect(BIRD_RECT_X_DEFAUT, SCREEN_HEIGHT / 2);
	p_menu_bg->SetRect(0, 0);
	p_bird->SetAngle(0);
	text[CURRENT_SC].SetRect(SCREEN_WIDTH / 2, 30);
	text[RECENT_SC].SetRect(206, 165);
	text[HIGH_SC].SetRect(206, 210);

	SDL_Color color = { 255, 255, 255, 255 };
	text[CURRENT_SC].SetColor(color);
	text[RECENT_SC].SetColor(color);
	text[HIGH_SC].SetColor(color);

	for (int i = 0; i < PIPE_NUM; i++) {
		int ranNum = p_pipe->GetRand(50,250);
		Pipe* p_top = (p_pipe + i)->GetPipeTop();
		Pipe* p_bot = (p_pipe + i)->GetPipeBot();
		if (!p_top->LoadImg("flappy-bird-assets//sprites//pipe-green-top.png", p_screen))	return false;
		if (!p_bot->LoadImg("flappy-bird-assets//sprites//pipe-green-bot.png", p_screen))	return false;
		p_top->SetRect(SCREEN_WIDTH + 200, -ranNum);
		p_bot->SetRect(SCREEN_WIDTH + 200, -ranNum + PIPE_DISTANCE + PIPE_HEIGHT);
	}

	if (!medal[NO].LoadImg("flappy-bird-assets//sprites//no_medal.png", p_screen))			return false;
	if (!medal[BRONZE].LoadImg("flappy-bird-assets//sprites//bronze_medal.png", p_screen))	return false;
	if (!medal[SILVER].LoadImg("flappy-bird-assets//sprites//siliver_medal.png", p_screen))	return false;
	if (!medal[GOLD].LoadImg("flappy-bird-assets//sprites//gold_medal.png", p_screen))		return false;

	medal[NO].SetRect(58, 178);
	medal[BRONZE].SetRect(58, 178);
	medal[SILVER].SetRect(58, 178);
	medal[GOLD].SetRect(58, 178);

	button[PLAY].LoadPath("flappy-bird-assets//sprites//button_sprites//play_button");
	button[OPTION].LoadPath("flappy-bird-assets//sprites//button_sprites//option_button");
	button[QUIT].LoadPath("flappy-bird-assets//sprites//button_sprites//quit_button");
	button[MUSIC].LoadPath("flappy-bird-assets//sprites//button_sprites//music_button");
	button[OK].LoadPath("flappy-bird-assets//sprites//button_sprites//ok_button");
	button[MENU].LoadPath("flappy-bird-assets//sprites//button_sprites//menu_button");

	if (!button[PLAY].IsLoadImg(p_screen))		return false;
	if (!button[OPTION].IsLoadImg(p_screen))	return false;
	if (!button[QUIT].IsLoadImg(p_screen))		return false;
	if (!button[MUSIC].IsLoadImg(p_screen))		return false;
	if (!button[OK].IsLoadImg(p_screen))		return false;
	if (!button[MENU].IsLoadImg(p_screen))		return false;

	button[PLAY].SetRect(94, 200);
	button[OPTION].SetRect(94, 265);
	button[QUIT].SetRect(94, 330);
	button[MUSIC].SetRect(248, 420);
	button[OK].SetRect(34, 260);
	button[MENU].SetRect(162, 260);

	sound[POINT] = Mix_LoadWAV("flappy-bird-assets//audio//point.wav");
	sound[HIT] = Mix_LoadWAV("flappy-bird-assets//audio//hit.wav");
	sound[DIE] = Mix_LoadWAV("flappy-bird-assets//audio//die.wav");
	sound[WING] = Mix_LoadWAV("flappy-bird-assets//audio//wing.wav");
	if (!sound[DIE] || !sound[WING] || !sound[POINT] || !sound[HIT])     return false;
	music_bg = Mix_LoadMUS("flappy-bird-assets//audio//music_bg.mp3");
	if (!music_bg)	return false;
	Mix_PlayMusic(music_bg, -1);
	p_font1 = TTF_OpenFont("flappy-bird-assets//text//FFFFORWA.ttf", 24);
	p_font2 = TTF_OpenFont("flappy-bird-assets//text//MinecraftTen-VGORe.ttf", 24);
	if (!p_font1 || !p_font2)	return false;
	return true;
}
void Game::Render()
{
	if (status_ == newGame) {
		this->InitGame();
		status_ = playing;
	}
	if (status_ == playing || status_ == colision) {
		SDL_SetRenderDrawColor(p_screen, 255, 255, 255, 255);
		SDL_RenderClear(p_screen);
		p_bg->Render(p_screen);
		p_bird->Render(p_screen);
		text[CURRENT_SC].LoadText(p_font1, p_screen);
		text[CURRENT_SC].Render(p_screen);
		for (int i = 0; i < PIPE_NUM; i++) {
			Pipe* p_top = (p_pipe + i)->GetPipeTop();
			Pipe* p_bot = (p_pipe + i)->GetPipeBot();
			p_top->Render(p_screen);
			p_bot->Render(p_screen);
		}
		if (status_ == colision && isPlayChanel) {
			Mix_PlayChannel(1, sound[HIT], 0);
			isPlayChanel = false;
		}
	}
	if (status_ == quit) {
		std::ofstream file("HighScore.txt");
		file << high_sc;
		file.close();
		exit(0);
	}
	if (status_ == die) {
		if (!isChunk) {
			Mix_PlayChannel(1, sound[HIT], 0);
			Mix_PlayChannel(2, sound[DIE], 0);
			isChunk = true;
		}
		p_sb->Render(p_screen);
		text[RECENT_SC].LoadText(p_font2, p_screen);
		text[HIGH_SC].LoadText(p_font2, p_screen);
		text[RECENT_SC].Render(p_screen);
		text[HIGH_SC].Render(p_screen);
		if (g_score <= 3) {
			medal[NO].Render(p_screen);
		}
		else if (g_score <= 7) {
			medal[BRONZE].Render(p_screen);
		}
		else if (g_score <= 10) {
			medal[SILVER].Render(p_screen);
		}
		else {
			medal[GOLD].Render(p_screen);
		}
		button[OK].Render(p_screen);
		button[MENU].Render(p_screen);
	}
	if (status_ == menu) {
		SDL_SetRenderDrawColor(p_screen, 255, 255, 255, 255);
		SDL_RenderClear(p_screen);
		p_menu_bg->Render(p_screen);
		if (isMusic) {
			Mix_VolumeMusic(40);
		}
		else {
			Mix_VolumeMusic(0);
		}
		renderBG = true;
		button[PLAY].RenderButton(p_screen);
		button[OPTION].RenderButton(p_screen);
		button[QUIT].RenderButton(p_screen);
		button[MUSIC].RenderButton(p_screen);
	}
	SDL_RenderPresent(p_screen);
	SDL_Delay(static_cast<Uint32>(1000 * deltaTime));
}
void Game::HandleEvent()
{
	SDL_PollEvent(events);
	if (status_ == menu) {
		if (button[PLAY].Selected(events)) {
			status_ = newGame;
			events->type = NULL;
		}
		if (button[QUIT].Selected(events)) {
			status_ = quit;
			events->type = NULL;
		}
		if (button[MUSIC].Selected(events)) {
			events->type = NULL;
			isMusic = !isMusic;
		}
	}
	if (status_ == playing) {
		if (events->type == SDL_MOUSEBUTTONDOWN) {
			start = true;
			p_bird->HandleFly(sound[WING]);
		}
		events->type = NULL;
	}
	if (status_ == die) {
		if (button[OK].Selected(events)) {
			status_ = newGame;
			events->type = NULL;
		}
		if (button[MENU].Selected(events)) {
			status_ = menu;
		}
	}
	if (events->type == SDL_QUIT) {
		status_ = quit;
	}
}
void Game::Update()
{
	if (status_ == playing) {
		text[CURRENT_SC].SetText(std::to_string(g_score));
		text[RECENT_SC].SetText(std::to_string(g_score));
		if (g_score > high_sc)	high_sc = g_score;
		text[HIGH_SC].SetText(std::to_string(high_sc));
		p_bird->Flapping(p_screen);
		if (start) {
			p_bird->HandleGravity();
			for (int i = 0; i < PIPE_NUM; i++) {
				(p_pipe + i)->HandleMove(SCREEN_WIDTH);
			}
		}
	}
	if (status_ == colision) {
		if (p_bird->GetRect().y < 369)	p_bird->HandleGravity();
		else status_ = die;
	}
}
void Game::Colision()
{
	if (status_ == playing) {
		for (int i = 0; i < PIPE_NUM; i++) {
			Pipe* p_top = p_pipe->GetPipeTop();
			Pipe* p_bot = p_pipe->GetPipeBot();
			if (status_ != colision) {
				if (p_bird->IsCollision(p_top->GetRect()) || p_bird->IsCollision(p_bot->GetRect())) {
					status_ = colision;
				}
			}
		}
		if (status_ != colision && p_bird->GetRect().y >= 370) {
			status_ = colision;
		}
	}
}
void Game::GetScore()
{
	if (status_ == playing) {
		Pipe* p_top = p_pipe->GetPipeTop();
		if (p_top->GetRect().x == p_bird->GetRect().x) {
			Mix_PlayChannel(-1, sound[POINT], 0);
			g_score++;
		}
	}
}