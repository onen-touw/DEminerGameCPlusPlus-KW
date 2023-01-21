#include "setting.h"


namespace gameSetting {
	SDL_Window* win = nullptr;
	SDL_Surface* surface = nullptr;

	difficult difficultG;
	winObjSizes winObjSize;
	fieldSettings fieldSetting;
	menuSettings menuSetting;

	short hardnessField = difficultG.easy;
	short hardnessBomb = difficultG.easy;
}
