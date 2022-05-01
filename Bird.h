#pragma once
#include "BaseObject.h"
#include "ConstSrc.h"
class Bird : public BaseObject
{
public:
	Bird();
	~Bird();
	void HandleFly(Mix_Chunk* fly_sound);
	void HandleGravity();
	bool IsFellGround();
	void Flapping(SDL_Renderer* des);
	void Render(SDL_Renderer* des);
	//bool Die()
private:
	float velY_;
	std::string pathBird[3] = { "flappy-bird-assets//sprites//bluebird-upflap.png",
							  "flappy-bird-assets//sprites//bluebird-midflap.png",
							  "flappy-bird-assets//sprites//bluebird-downflap.png" };
	int frame_;
	double timeFrame_;
	double timeFly_;
	double angle_;
};