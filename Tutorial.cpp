#include "Tutorial.h"
Tutor::Tutor() {
	frame_ = 0;
	timeFrame_ = 0;
	for (int i = 0; i < 2; i++) {
		mouse[i] = new PicObject;
	}
	mouse[MOUSE_RIGHT]->SetRect(35, SCREEN_HEIGHT / 2 - 5);
	mouse[MOUSE_LEFT]->SetRect(130, SCREEN_HEIGHT / 2 - 5);
	p_text[TEXT_TUR].SetColor({ 255, 0, 0, 255 });
	p_text[TEXT_ESC].SetColor({ 250, 0, 0, 255 });
	p_text[TEXT_TUR].SetRect(10, SCREEN_HEIGHT / 2 + 20);
	p_text[TEXT_ESC].SetRect(10, SCREEN_HEIGHT / 2 + 50);
	p_text[TEXT_TUR].SetText("CLICK       OR      TO FLY");
	p_text[TEXT_ESC].SetText("   PRESS ESC TO CONTINUE  ");
}
Tutor::~Tutor() {
	if (!p_text)	delete[] p_text;
	for (int i = 0; i < 3; i++) {
		if (!mouse[i])	delete[] mouse[i];
	}
	delete[] mouse;
}
void Tutor::Render(TTF_Font* font, SDL_Renderer* des)
{
	timeFrame_ += deltaTime;
	p_text[TEXT_TUR].LoadText(font, des);
	p_text[TEXT_TUR].Render(des);
	p_text[TEXT_ESC].LoadText(font, des);
	p_text[TEXT_ESC].Render(des);
	if (timeFrame_ >= 20 * deltaTime) {
		frame_++;
		if (frame_ > 1)	frame_ = 0;
		timeFrame_ = 0;
	}
	if (frame_ == 0) {
		mouse[MOUSE_RIGHT]->LoadImg(path_mouse[0], des);
		mouse[MOUSE_LEFT]->LoadImg(path_mouse[0], des);
	}
	else if (frame_ == 1) {
		mouse[MOUSE_RIGHT]->LoadImg(path_mouse[1], des);
		mouse[MOUSE_LEFT]->LoadImg(path_mouse[2], des);
	}
	mouse[MOUSE_RIGHT]->Render(des);
	mouse[MOUSE_LEFT]->Render(des);
}