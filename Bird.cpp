#include "Bird.h"
Bird::Bird()
{
	velY_ = 0;
	frame_ = 0;
	timeFrame_ = 0;
	timeFly_ = 0;
	angle_ = 0;
}
Bird::~Bird()
{
}
void Bird::HandleGravity()
{
	timeFly_ += deltaTime;
	int y = rect_.y;
	y += velY_ + 0.6;
	velY_ += 0.5;
	angle_ = (velY_ / 2) * 10 - 5;
	if (y <= -BIRD_HEIGHT)	y = -BIRD_HEIGHT;
	this->SetRect(rect_.x, y);
}
void Bird::HandleFly(Mix_Chunk* fly_sound)
{
	velY_ = -6;
	int y = rect_.y;
	y -= 30;
	Mix_PlayChannel(1, fly_sound, 0);
}
bool Bird::IsFellGround()
{
	int y = rect_.y;
	if (rect_.y > SCREEN_HEIGHT - BIRD_HEIGHT)	return true;
	else return false;
}
void Bird::Flapping(SDL_Renderer* des)
{
	timeFrame_ += deltaTime;
	if (timeFrame_ == 3 * deltaTime) {
		frame_++;
		if (frame_ > 2)	frame_ = 0;
		timeFrame_ = 0;
	}
	this->LoadImg(pathBird[frame_], des);
	this->Render(des);
}
void Bird::Render(SDL_Renderer* des)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopyEx(des, p_object_, NULL, &renderquad, angle_, NULL, SDL_FLIP_NONE);
}