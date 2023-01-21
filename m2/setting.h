#pragma once

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<vector>

struct cell_values
{
	short int i = 0;
	short int j = 0;
	short int x = 0;
	short int y = 0;
	bool bomb = false;				// - bomb (1 - true) 
	bool open = false;				//- open? (1 - true) 
	bool flag = false;				//has flag? (1 - true)
	bool question = false;			//has question (1 - true)
	short int bmb_near = 0;		//bombs are near (count) 
};

enum gameStatus {
	lose,win
};

struct fieldSettings
{
	enum gameImg
	{
		cell,
		openCell,
		numbers,
		flag,
		question,
		bomb,

		gameImgTOTAL
	};
	
	short numberCropSize = 300;
};

struct difficult
{
	short hEasy = 17;
	short wEasy = 17;

	short hNorm = 22;
	short wNorm = 22;

	short hHard = 27;
	short wHard = 27;

	short gH = 0;
	short gW = 0;
	short bombDensity = 0;

	/// уровень сложности для поля
	void updateFieldSize(int i)
	{
		switch (i)
		{
		case hLvl::easy:
			this->gH = this->hEasy;
			this->gW = this->wEasy;
			break;
		case hLvl::normal:
			this->gH = this->hNorm;
			this->gW = this->wNorm;
			break;
		case hLvl::hard:
			this->gH = this->hHard;
			this->gW = this->wHard;
			break;

		default:
			break;
		}
	}

	/// уровень сложности для кол-ва мин
	void updateBombDensity(int i) {
		switch (i)
		{
		case hLvl::easy:
			this->bombDensity = 10;
			break;
		case hLvl::normal:
			this->bombDensity = 6;
			break;
		case hLvl::hard:
			this->bombDensity = 5;
			break;
		default:
			break;
		}
	}

	enum hLvl
	{
		easy,
		normal,
		hard
	};
};

struct winObjSizes
{
	short int cellSize = 30;		//px
	
	short int HeaderHeight = 50;	//px

	short int winWIDTH = 0;			//px
	short int winHEIGHT = 0;		//px

	void update(short gH,short gW) {
		this->winHEIGHT = (gH - 2) * this->cellSize + this->HeaderHeight;
		this->winWIDTH = (gW - 2) * this->cellSize;
	}
};


struct position
{
	short i = 0;
	short j = 0;
};


struct menuSettings
{
	int menuPaddingTop = 5;
	int menuPadingLeft = 20;
	int cropHeightImgBtn = 150;
	int heightImgBtn = 95;
	int widthImgBtns = 300;
	const int menu2LvlPunctsCount = 2; ///about, settings

	enum headerImg
	{
		headerBg,
		numberss,
		smile,
		xSign,
		winSign,
		loseSign,

		headerImgTOTAL
	};

	enum menuImg
	{
		BG,
		numbers,
		menuFirstLvlBtns,
		menuSettingsBtns,
		rootBtns,
		flag,
		bomb,

		imgMenuTOTAL
	};
	enum menu2lvlPuncts
	{
		goTo1lvl,
		settingsP,
		aboutP
	};
	enum rootBtn
	{
		accept,
		cancel,
		rootTOTAL
	};
	enum menuPuncts
	{
		statistic,
		settings,
		about,
		cancelBtn,
		quitBtn,

		menuPunctsTOTAL
	};
	enum menuSettingPuncts
	{
		easyBmb = 0,
		normalBmb,
		hardBmb,
		smallF,
		mediumF,
		largeF,


		menuSettingPunctsTOTAL
	};
};




namespace gameSetting {
	extern SDL_Window* win;
	extern SDL_Surface* surface;

	extern difficult difficultG;
	extern winObjSizes winObjSize;
	extern fieldSettings fieldSetting;
	extern menuSettings menuSetting;

	extern short hardnessField;
	extern short hardnessBomb;
}

