#include "GameObject.h"
#undef main

int main(int arg, char* argv[])
{
	SDL_ShowCursor(SDL_DISABLE);
	Game* p_Game = new Game;
	p_Game->HandleEvent();
	if (!p_Game->InitSDL())		return -1;
	if (!p_Game->InitGame())	return -1;
	while (!p_Game->isQuitGame()) {
		p_Game->HandleEvent();
		p_Game->Render();
		p_Game->Update();
		p_Game->GetScore();
		p_Game->GameOver();
	}
	delete p_Game;	
	return 0;
}