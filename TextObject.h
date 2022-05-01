#pragma once
#include "BaseObject.h"
class TextObject : public BaseObject
{
public:
	TextObject();
	~TextObject();
	void SetText(const std::string& text);
	void SetColor(SDL_Color color);
	void LoadText(TTF_Font* font, SDL_Renderer* des);
	//void SetRect(int x, int y, int w, int h);
	void Render(SDL_Renderer* des);
private:
	std::string text_val_;
	SDL_Color text_color_;
};