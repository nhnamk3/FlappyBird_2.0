#include "GameObject.h"
Game::Game()
{
	std::ifstream file("HighScore.txt");
	file >> high_sc;
	file.close();
}
Game::~Game()
{
	if (!p_backGround)	delete p_backGround;
	if (!p_scoreBoard)	delete p_scoreBoard;
	if (!p_menu_bg)		delete p_menu_bg;
	if (!p_tutor)		delete p_tutor;
	if (!p_bird)		delete p_bird;
	if (!p_pipe)		delete p_pipe;
	if (!events)		delete events;
	if (!p_window)		SDL_DestroyWindow(p_window);
	if (!p_screen)		SDL_DestroyRenderer(p_screen);
	if (!music_bg)		Mix_FreeMusic(music_bg);
	if (!text)			delete[] text;
	if (!button)		delete[] button;
	if (!medal)			delete[] medal;
	for (int i = 0; i < NUM_FONT; i++) {
		if (!font[i])	TTF_CloseFont(font[i]);
	}
	for (int i = 0; i < NUM_SOUND; i++) {
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
	if (rand() % 2) {
		if (!p_backGround->LoadImg("flappy-bird-assets//sprites//background-day.png", p_screen))		return false;
	}else {
		if (!p_backGround->LoadImg("flappy-bird-assets//sprites//background-night.png", p_screen))		return false;
	}
	if (!p_scoreBoard->LoadImg("flappy-bird-assets//sprites//score_board.png", p_screen))				return false;
	if (!p_bird->LoadImg("flappy-bird-assets//sprites//bluebird-midflap.png", p_screen))				return false;
	if (!p_menu_bg->LoadImg("flappy-bird-assets//sprites//menu_bg.png", p_screen))						return false;	

	p_backGround->SetRect(0, 0);
	p_scoreBoard->SetRect(0, 0);
	p_bird->SetRect(BIRD_RECT_X_DEFAUT, SCREEN_HEIGHT / 2);
	p_menu_bg->SetRect(0, 0);
	p_bird->SetAngle(0);

	font[fCURRENT_SC] = TTF_OpenFont("flappy-bird-assets//text//FFFFORWA.ttf", 24);
	font[fFINAL_SC] = TTF_OpenFont("flappy-bird-assets//text//MinecraftTen-VGORe.ttf", 24);
	font[fTUTOR] = TTF_OpenFont("flappy-bird-assets//text//Tutorial_text.ttf", 24);
	font[fMESS] = TTF_OpenFont("flappy-bird-assets//text//MinecraftTen-VGORe.ttf", 32);
	if (!font[fCURRENT_SC] || !font[fFINAL_SC] || !font[fTUTOR] || !font[fMESS])	return false;

	text[tCURRENT_SC].SetRect(SCREEN_WIDTH / 2, 30);
	text[tFINAL_SC].SetRect(206, 165);
	text[tHIGH_SC].SetRect(206, 210);
	text[tMess].SetRect(40, 160);

	SDL_Color white_color = { 255, 255, 255, 255 };
	SDL_Color green_color = { 0, 155, 0, 255 };
	text[tCURRENT_SC].SetColor(white_color);
	text[tFINAL_SC].SetColor(white_color);
	text[tHIGH_SC].SetColor(white_color);
	text[tMess].SetColor(green_color);
	text[tMess].SetText("COMING SOON");
	text[tMess].LoadText(font[fMESS], p_screen);

	for (int i = 0; i < PIPE_NUM; i++) {
		int ranNum = p_pipe->GetRand(50,250);
		Pipe* p_top = (p_pipe + i)->GetPipeTop();
		Pipe* p_bot = (p_pipe + i)->GetPipeBot();
		if (!p_top->LoadImg("flappy-bird-assets//sprites//pipe-green-top.png", p_screen))			return false;
		if (!p_bot->LoadImg("flappy-bird-assets//sprites//pipe-green-bot.png", p_screen))			return false;
		p_top->SetRect(SCREEN_WIDTH + 200, -ranNum);
		p_bot->SetRect(SCREEN_WIDTH + 200, -ranNum + PIPE_DISTANCE + PIPE_HEIGHT);
	}

	if (!medal[mNO].LoadImg("flappy-bird-assets//sprites//no_medal.png", p_screen))					return false;
	if (!medal[mBRONZE].LoadImg("flappy-bird-assets//sprites//bronze_medal.png", p_screen))			return false;
	if (!medal[mSILVER].LoadImg("flappy-bird-assets//sprites//siliver_medal.png", p_screen))		return false;
	if (!medal[mGOLD].LoadImg("flappy-bird-assets//sprites//gold_medal.png", p_screen))				return false;

	medal[mNO].SetRect(58, 178);
	medal[mBRONZE].SetRect(58, 178);
	medal[mSILVER].SetRect(58, 178);
	medal[mGOLD].SetRect(58, 178);

	button[bPLAY].LoadPath("flappy-bird-assets//sprites//button_sprites//play_button");
	button[bOPTION].LoadPath("flappy-bird-assets//sprites//button_sprites//option_button");
	button[bQUIT].LoadPath("flappy-bird-assets//sprites//button_sprites//quit_button");
	button[bMUSIC].LoadPath("flappy-bird-assets//sprites//button_sprites//music_button");
	button[bOK].LoadPath("flappy-bird-assets//sprites//button_sprites//ok_button");
	button[bMENU].LoadPath("flappy-bird-assets//sprites//button_sprites//menu_button");
	button[bTUTOR].LoadPath("flappy-bird-assets//sprites//button_sprites//HTP_button");

	if (!button[bPLAY].IsLoadImg(p_screen))		return false;
	if (!button[bOPTION].IsLoadImg(p_screen))	return false;
	if (!button[bQUIT].IsLoadImg(p_screen))		return false;
	if (!button[bMUSIC].IsLoadImg(p_screen))	return false;
	if (!button[bOK].IsLoadImg(p_screen))		return false;
	if (!button[bMENU].IsLoadImg(p_screen))		return false;
	if (!button[bTUTOR].IsLoadImg(p_screen))	return false;

	button[bPLAY].SetRect(94, 200);
	button[bOPTION].SetRect(94, 265);
	button[bQUIT].SetRect(94, 330);
	button[bMUSIC].SetRect(248, 420);
	button[bOK].SetRect(34, 260);
	button[bMENU].SetRect(162, 260);
	button[bTUTOR].SetRect(0, 420);

	sound[sPOINT] = Mix_LoadWAV("flappy-bird-assets//audio//point.wav");
	sound[sHIT] = Mix_LoadWAV("flappy-bird-assets//audio//hit.wav");
	sound[sDIE] = Mix_LoadWAV("flappy-bird-assets//audio//die.wav");
	sound[sWING] = Mix_LoadWAV("flappy-bird-assets//audio//wing.wav");
	sound[sCLICK] = Mix_LoadWAV("flappy-bird-assets//audio//click.wav");
	if (!sound[sDIE] || !sound[sWING] || !sound[sPOINT] || !sound[sHIT] || !sound[sCLICK])     return false;
	music_bg = Mix_LoadMUS("flappy-bird-assets//audio//music_bg.mp3");
	if (!music_bg)	return false;
	Mix_PlayMusic(music_bg, -1);

	return true;
}
void Game::Render()
{ 
	if (isMusic) {
		Mix_VolumeMusic(40);
		Mix_VolumeChunk(sound[sCLICK], 20);
		Mix_VolumeChunk(sound[sWING], 10);
		Mix_VolumeChunk(sound[sDIE], 10);
		Mix_VolumeChunk(sound[sPOINT], 10);
		Mix_VolumeChunk(sound[sHIT], 10);
	}
	else {
		Mix_VolumeMusic(0);
		Mix_VolumeChunk(sound[sCLICK], 0);
		Mix_VolumeChunk(sound[sWING], 0);
		Mix_VolumeChunk(sound[sDIE], 0);
		Mix_VolumeChunk(sound[sPOINT], 0);
		Mix_VolumeChunk(sound[sHIT], 0);
	}
	if (status_ == newGame) {
		this->InitGame();
		g_score = 0;
		start = false;
		renderBG = false;
		isChunk = false;
		isPlayChanel = true;
		status_ = playing;
	}
	if (status_ == menu) {
		SDL_SetRenderDrawColor(p_screen, 255, 255, 255, 255);
		SDL_RenderClear(p_screen);
		p_menu_bg->Render(p_screen);
		renderBG = true;
		button[bPLAY].RenderButton(p_screen);
		button[bOPTION].RenderButton(p_screen);
		button[bQUIT].RenderButton(p_screen);
		button[bMUSIC].RenderButton(p_screen);
		button[bTUTOR].RenderButton(p_screen);
		if (showMess) {
			time += deltaTime;
			text[tMess].Render(p_screen);
			if (time >= 40 * deltaTime) {
				events->type = NULL;
				time = 0;
				showMess = false;
			}
		}
	}
	if (status_ == playing || status_ == colision) {
		SDL_SetRenderDrawColor(p_screen, 255, 255, 255, 255);
		SDL_RenderClear(p_screen);
		p_backGround->Render(p_screen);
		p_bird->Render(p_screen);
		text[tCURRENT_SC].LoadText(font[fCURRENT_SC], p_screen);
		text[tCURRENT_SC].Render(p_screen);
		for (int i = 0; i < PIPE_NUM; i++) {
			Pipe* p_top = (p_pipe + i)->GetPipeTop();
			Pipe* p_bot = (p_pipe + i)->GetPipeBot();
			p_top->Render(p_screen);
			p_bot->Render(p_screen);
		}
		if (status_ == colision && isPlayChanel) {
			Mix_PlayChannel(1, sound[sHIT], 0);
			isPlayChanel = false;
		}
	}
	if (status_ == die) {
		if (!isChunk) {
			Mix_PlayChannel(1, sound[sHIT], 0);
			Mix_PlayChannel(2, sound[sDIE], 0);
			isChunk = true;
		}
		p_scoreBoard->Render(p_screen);
		text[tFINAL_SC].LoadText(font[fFINAL_SC], p_screen);
		text[tHIGH_SC].LoadText(font[fFINAL_SC], p_screen);
		text[tFINAL_SC].Render(p_screen);
		text[tHIGH_SC].Render(p_screen);
		if (g_score <= 3) {
			medal[mNO].Render(p_screen);
		}
		else if (g_score <= 7) {
			medal[mBRONZE].Render(p_screen);
		}
		else if (g_score <= 10) {
			medal[mSILVER].Render(p_screen);
		}
		else {
			medal[mGOLD].Render(p_screen);
		}
		button[bOK].Render(p_screen);
		button[bMENU].Render(p_screen);
	}
	if (status_ == tutor) {
		SDL_SetRenderDrawColor(p_screen, 255, 255, 255, 255);
		SDL_RenderClear(p_screen);
		p_menu_bg->Render(p_screen);
		p_tutor->Render(font[fTUTOR], p_screen);
	}
	if (status_ == quit) {
		std::ofstream file("HighScore.txt");
		file << high_sc;
		file.close();
		exit(0);
	}
	SDL_RenderPresent(p_screen);
	SDL_Delay(static_cast<Uint32>(1000 * deltaTime));
}
void Game::HandleEvent()
{
	SDL_PollEvent(events);
	if (status_ == menu) {
		if (button[bPLAY].Selected(events, sound[sCLICK])) {
			status_ = newGame;
			events->type = NULL;
		}
		if (button[bQUIT].Selected(events, sound[sCLICK])) {
			status_ = quit;
			events->type = NULL;
		}
		if (button[bMUSIC].Selected(events, sound[sCLICK])) {
			isMusic = !isMusic;
			events->type = NULL;
		}
		if (button[bTUTOR].Selected(events, sound[sCLICK])) {
			status_ = tutor;
			events->type = NULL;
		}
		if (button[bOPTION].Selected(events, sound[sCLICK])) {
			showMess = true; 
			events->type = NULL;
		}
	}
	if (status_ == playing) {
		if (events->type == SDL_MOUSEBUTTONDOWN) {
			start = true;
			p_bird->HandleFly(sound[sWING]);
		}
		events->type = NULL;
	}
	if (status_ == die) {
		if (button[bOK].Selected(events, sound[sCLICK])) {
			status_ = newGame;
			events->type = NULL;
		}
		if (button[bMENU].Selected(events, sound[sCLICK])) {
			status_ = menu;
			events->type = NULL;
		}
	}
	if (status_ == tutor) {
		if (events->key.keysym.sym == SDLK_ESCAPE) {
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
		text[tCURRENT_SC].SetText(std::to_string(g_score));
		text[tFINAL_SC].SetText(std::to_string(g_score));
		if (g_score > high_sc)	high_sc = g_score;
		text[tHIGH_SC].SetText(std::to_string(high_sc));
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
			Mix_PlayChannel(-1, sound[sPOINT], 0);
			g_score++;
		}
	}
}