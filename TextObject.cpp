#include "TextObject.h"
TextObject::TextObject() {};
TextObject::~TextObject() {};
void TextObject::SetText(const std::string& text)
{
	text_val_ = text;
}
void TextObject::SetColor(SDL_Color color)
{
	text_color_ = color;
}
void TextObject::LoadText(TTF_Font* font, SDL_Renderer* des)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text_val_.c_str(), text_color_);
	p_object_ = SDL_CreateTextureFromSurface(des, surface);
	SDL_FreeSurface(surface);
}
void TextObject::Render(SDL_Renderer* des)
{
	int textW = 0;
	int textH = 0;
	SDL_QueryTexture(p_object_, NULL, NULL, &textW, &textH);
	rect_.w = textW;
	rect_.h = textH;
	SDL_RenderCopy(des, p_object_, NULL, &rect_);
}