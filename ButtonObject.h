#pragma once
#include "BaseObject.h"
class Button : public BaseObject
{
public:
	Button();
	~Button();
	void Update();
	void Handle();
	bool Selected(SDL_Event* e, Mix_Chunk* sound);
	void RenderButton(SDL_Renderer* des);
	void LoadPath(const std::string& FileName);
	bool IsLoadImg(SDL_Renderer* des);
private:
	bool selected_ = false;
	bool bl = true;	// true : trang thai cua button bat, false: trang thai cua button tat
	std::string pathFile[2];
	bool Colision = false;
};