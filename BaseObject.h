#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include "ConstSrc.h"
class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y);
	SDL_Rect GetRect();
	SDL_Texture* GetObject();
	virtual bool LoadImg(const std::string& FileName, SDL_Renderer* screen);
	bool IsCollision(SDL_Rect other);
	virtual void Render(SDL_Renderer* des);
	void Free();
protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};