#pragma once
#include "BaseObject.h"
#include "TextObject.h"
#include "PicObject.h"
class Tutor : public BaseObject
{
public:
	enum MouseName {
		MOUSE_RIGHT, MOUSE_LEFT
	};
	enum TextName {
		TEXT_TUR, TEXT_ESC
	};
	Tutor();
	~Tutor();
	void Render(TTF_Font* font, SDL_Renderer* des);
private:
	TextObject* p_text = new TextObject[2];
	PicObject** mouse = new PicObject*[2];
	std::string path_mouse[3] = { "flappy-bird-assets//sprites//mouse.png",
							"flappy-bird-assets//sprites//mouse_right.png",
							"flappy-bird-assets//sprites//mouse_left.png" };
	int frame_;
	double timeFrame_;
};