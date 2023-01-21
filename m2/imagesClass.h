#pragma once


#include"setting.h"

class imagesClass
{
protected:
	std::vector<SDL_Surface*>images;

public:

	void setImgVectSize(int size) {
		images.resize(size);
	}

	void loadImg(std::string path, int position) {
		

		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == NULL) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			return;
		}
		flower = SDL_ConvertSurface(flower, gameSetting::surface->format, NULL);
		if (flower == NULL) {
			std::cout << "Can't convert: " << SDL_GetError() << std::endl;
			return;
		}
		images[position] = flower;
		return;
	}

	//SDL_Surface* loadImg(std::string path) {
	//	SDL_Surface* flower = IMG_Load(path.c_str());
	//	if (flower == NULL) {
	//		std::cout << "Can't load: " << IMG_GetError() << std::endl;
	//		return;
	//	}
	//	flower = SDL_ConvertSurface(flower, gameSetting::surface->format, NULL);
	//	if (flower == NULL) {
	//		std::cout << "Can't convert: " << SDL_GetError() << std::endl;
	//		return;
	//	}
	//	return flower;
	//}

	~imagesClass()
	{
		images.clear();
	}

};

