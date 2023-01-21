#pragma once

#include"setting.h"

class baseGameClass
{
protected:

public:

	~baseGameClass()
	{

	}

	baseGameClass()
	{
		gameSetting::difficultG.updateFieldSize(gameSetting::hardnessField);
		gameSetting::difficultG.updateBombDensity(gameSetting::hardnessBomb);
		gameSetting::winObjSize.update(gameSetting::difficultG.gH, gameSetting::difficultG.gW);
		std::cout << gameSetting::winObjSize.winHEIGHT << "x" << gameSetting::winObjSize.winWIDTH << " \n";
		this->initModuls();
	}

	bool initModuls() {
		bool success = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			success = false;
		}
		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			success = false;
		}
		
		gameSetting::win = SDL_CreateWindow("DeminerGame", 100, 50, 
			gameSetting::winObjSize.winWIDTH, gameSetting::winObjSize.winHEIGHT, SDL_WINDOW_SHOWN);
		
		if (gameSetting::win == NULL) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		gameSetting::surface = SDL_GetWindowSurface(gameSetting::win);

		if (TTF_Init() != 0)
		{
			success = false;
			std::cout << "TTF init ERROR: " << SDL_GetError() << std::endl;

		}

		return success;
	}

	bool rebuildWin() {
		bool success = true;
		SDL_FreeSurface(gameSetting::surface);
		SDL_DestroyWindow(gameSetting::win);

		gameSetting::winObjSize.update(gameSetting::difficultG.gH, gameSetting::difficultG.gW);
		std::cout << gameSetting::winObjSize.winHEIGHT << "x" << gameSetting::winObjSize.winWIDTH << " \n";

		gameSetting::win = SDL_CreateWindow("DeminerGame", 100, 50,
			gameSetting::winObjSize.winWIDTH, gameSetting::winObjSize.winHEIGHT, SDL_WINDOW_SHOWN);

		if (gameSetting::win == NULL) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		gameSetting::surface = SDL_GetWindowSurface(gameSetting::win);

		return success;
	}

};

