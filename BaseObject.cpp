#include "BaseObject.h"
BaseObject::BaseObject()
{
	p_object_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}
BaseObject::~BaseObject()
{
	Free();
}
void BaseObject::SetRect(const int& x, const int& y)
{
	rect_.x = x;
	rect_.y = y;
}
SDL_Rect BaseObject::GetRect()
{
	return rect_;
}
SDL_Texture* BaseObject::GetObject()
{
	if (!p_object_)	return p_object_;
}
bool BaseObject::LoadImg(const std::string& FileName, SDL_Renderer* screen)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* load_surface = IMG_Load(FileName.c_str());
	if (load_surface == NULL)	return false;
	else {
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 255, 255, 255));
		newTexture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (newTexture == NULL)	return false;
		else {
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object_ = newTexture;
	return p_object_ != NULL;
}
void BaseObject::Render(SDL_Renderer* des)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopy(des, p_object_, NULL, &renderquad);
}
bool BaseObject::IsCollision(SDL_Rect other)
{
    int left_a = rect_.x;
    int right_a = rect_.x + rect_.w;
    int top_a = rect_.y;
    int bottom_a = rect_.y + rect_.h;

    int left_b = other.x;
    int right_b = other.x + other.w;
    int top_b = other.y;
    int bottom_b = other.y + other.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}
void BaseObject::Free()
{
	if (p_object_ != NULL) {
		SDL_DestroyTexture(p_object_);
		p_object_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}