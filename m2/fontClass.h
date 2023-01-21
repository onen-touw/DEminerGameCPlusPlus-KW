#pragma once

#include"setting.h"


class fontClass
{

protected:
	TTF_Font* font = nullptr;
	SDL_Color color = { 148, 0, 211 };

public:

	fontClass() {
		this->font = TTF_OpenFont("./font/courier.ttf", 20);
		if (this->font == nullptr)
		{

			std::cout << "ttf load font error\n";
		}

		std::cout << "fontLoad\n";
	}

	~fontClass()
	{
		TTF_CloseFont(this->font);
	}

	SDL_Surface* blitTxt(TTF_Font* font, SDL_Color color, const char* text, SDL_Rect rect)
	{
		SDL_Surface* tempSurf = TTF_RenderText_Blended_Wrapped(font,text, color, 400);
		if (tempSurf == nullptr)
		{
			std::cout << "ttf surface error\n";

		}
		SDL_BlitSurface(tempSurf, NULL, gameSetting::surface, &rect);
		SDL_UpdateWindowSurface(gameSetting::win);

		return tempSurf;
	}

};

