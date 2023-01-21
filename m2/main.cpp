
#include"gameplayClass.h"
#include"setting.h"

int main(int argc, char* argv[]) {


	gameplayClass game;

	game.startGame();
	
	SDL_FreeSurface(gameSetting::surface);
	SDL_DestroyWindow(gameSetting::win);

	SDL_Quit();
	IMG_Quit();


	return 0;
}