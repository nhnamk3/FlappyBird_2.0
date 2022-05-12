#include "ButtonObject.h"
Button::Button()
{}
Button::~Button()
{}
void Button::Update()
{}
void Button::Handle()
{}
bool Button::Selected(SDL_Event* e, Mix_Chunk* sound)
{
	selected_ = false;
	SDL_PollEvent(e);
	if (e->type == SDL_MOUSEBUTTONUP) {
		int x = e->motion.x;
		int y = e->motion.y;
		if (x >= rect_.x && x <= (rect_.x + rect_.w) && y >= rect_.y && y <= (rect_.y + rect_.h)) {
			selected_ = true;
			bl = !bl;
			Mix_PlayChannel(1, sound, 0);
		}
	}
	return selected_;
}
void Button::RenderButton(SDL_Renderer* des)
{
	if (bl) {
		this->LoadImg(pathFile[0], des);
		this->Render(des);
	}
	else {
		this->LoadImg(pathFile[1], des);
		this->Render(des);
	}
}
void Button::LoadPath(const std::string& FileName)
{
	pathFile[0] = FileName + "_1.png";
	pathFile[1] = FileName + "_2.png";
}
bool Button::IsLoadImg(SDL_Renderer* des)
{
	if (!this->LoadImg(pathFile[0], des))	return false;
	if (!this->LoadImg(pathFile[1], des))	return false;
	return true;
}