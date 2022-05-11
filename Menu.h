#pragma once
#include "BaseObject.h"
class Menu : public BaseObject
{
public:
	Menu();
	~Menu();
	void Render(SDL_Renderer* des, TTF_Font* p_font);
	void HandleEvents(SDL_Event events);
	bool* GetSelect();
private:
	SDL_Surface* menus_[MENU_NUM];
	SDL_Texture* menus[MENU_NUM];
	std::string labels[MENU_NUM] = { "Play", "Exit" };
	SDL_Rect pos[MENU_NUM];
	SDL_Color colors[2] = { {255, 255, 255}, {255, 0, 0} };
	bool Selected[MENU_NUM] = { false, false };
};