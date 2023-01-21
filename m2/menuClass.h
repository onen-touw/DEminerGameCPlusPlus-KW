#pragma once

#include"imagesClass.h"
#include"fontClass.h"
#include<string>

class menuClass : public imagesClass, public fontClass
{

private:
	bool menuFlag = false;


	int winWidth = gameSetting::winObjSize.winWIDTH;
	int winHeight = gameSetting::winObjSize.winHEIGHT;

	int menuWidth = 400;
	int menuY = gameSetting::winObjSize.HeaderHeight + 20;

	int menuBtnsHeight = 40;
	int menuBtnsWidth = 110;

	int PadingLeft = gameSetting::menuSetting.menuPadingLeft;
	int PadingTop = gameSetting::menuSetting.menuPaddingTop;

	int menuSecondLvl = -1;

	int hardnessSettingFieldTemp = 0;
	int hardnessSettingBombTemp = 0;

	std::vector<SDL_Rect>mainBtnsRects;
	std::vector<SDL_Rect>settingBtnsRects;
	std::vector<SDL_Rect>rootBtnRects;

	int statGC = 0;
	std::vector<std::vector<int>>stat;
public:

	void updateSizes() {
		this-> winWidth = gameSetting::winObjSize.winWIDTH;
		this->winHeight = gameSetting::winObjSize.winHEIGHT;
	}

	void setBtnsRects() {
		SDL_Rect mr;
		for (int i = 0; i < this->mainBtnsRects.size(); i++)
		{
			mr = {
				this->winWidth / 2 - this->menuBtnsWidth / 2,
				this->menuY + this->PadingTop + i * (this->menuBtnsHeight + this->PadingTop),
				this->menuBtnsWidth,
				this->menuBtnsHeight
			};
			this->mainBtnsRects[i] = mr;
		}
		for (int i = 0; i < this->settingBtnsRects.size(); i++)
		{
			mr = {
				this->winWidth / 2 - this->menuBtnsWidth / 2,
				this->menuY + this->PadingTop + i * (this->menuBtnsHeight + this->PadingTop),
				this->menuBtnsWidth,
				this->menuBtnsHeight
			};
			this->settingBtnsRects[i] = mr;
		}

		mr = { this->winWidth / 2 - this->menuBtnsWidth,
			this->winHeight - this->menuY - 2 * this->PadingTop - this->menuBtnsHeight,
			this->menuBtnsWidth,
			this->menuBtnsHeight
		};
		rootBtnRects[gameSetting::menuSetting.rootBtn::accept] = mr;

		mr = { this->winWidth / 2,
			this->winHeight - this->menuY - 2 * this->PadingTop - this->menuBtnsHeight,
			this->menuBtnsWidth,
			this->menuBtnsHeight
		};
		rootBtnRects[gameSetting::menuSetting.rootBtn::cancel] = mr;

	}

	void setHardnessF(int hSf) {
		this->hardnessSettingFieldTemp = hSf;
	}
	void setHardnessB(int hSb) {
		this->hardnessSettingBombTemp = hSb;
	}
	void updateHardSetting() {
		gameSetting::hardnessBomb = this->hardnessSettingBombTemp;
		gameSetting::hardnessField = this->hardnessSettingFieldTemp;
	}

	menuClass(){
		this->mainBtnsRects.resize(gameSetting::menuSetting.menuPuncts::menuPunctsTOTAL);
		this->settingBtnsRects.resize(gameSetting::menuSetting.menuSettingPuncts::menuSettingPunctsTOTAL);
		this->rootBtnRects.resize(gameSetting::menuSetting.rootBtn::rootTOTAL);
		this->setBtnsRects();
	}
	~menuClass()
	{

	}

	void blitMenuBg() {
		SDL_Rect motion_rect = { this->winWidth / 2 - this->menuWidth / 2 ,
			this->menuY,
			this->menuWidth,
			this->winHeight - this->menuY - 2 * this->PadingTop
		};
		SDL_BlitScaled(this->images[gameSetting::menuSetting.menuImg::BG], NULL, gameSetting::surface, &motion_rect);
	}

	void blitMainButtons() {
		for (int i = 0; i < this->mainBtnsRects.size(); i++)
		{
			SDL_Rect cr = { 0, 30 * i, this->menuBtnsWidth, 30 };
			SDL_BlitScaled(this->images[gameSetting::menuSetting.menuImg::menuFirstLvlBtns],
				&cr, gameSetting::surface, &this->mainBtnsRects[i]);
		}
	}


	//отрисовка окна "menu" (update - для единичного вызова в игровом цикле и обновления)
	void blitWinMenu(bool update) {
		static int v = 0;
		//std::cout << v << " vvv\n";
		if (v == 0 && !update)
		{
			this->menuFlag = true;
			this->blitMenuBg();
			blitMainButtons();
			SDL_UpdateWindowSurface(gameSetting::win);
			v++;
		}
		else if (v > 0 && !update)
		{
			return;
		}
		else if (v > 0 && update)
		{
			v = 0;
			return;
		}
	}

	bool getMenuFlag() { return this->menuFlag; }
	void toggleFlag() { this->menuFlag ? this->menuFlag = false : this->menuFlag = true; }

	std::vector<SDL_Rect>getMainBtnV() { return this->mainBtnsRects; }
	std::vector<SDL_Rect>getSettingBtnV() { return this->settingBtnsRects; }
	std::vector<SDL_Rect>getRootBtnV() { return this->rootBtnRects; }

	void menuSetSecondLvl(int i) { this->menuSecondLvl = i; }
	int getSecondLvl() { return this->menuSecondLvl; }

	int btnParse(std::vector<SDL_Rect>V, int x,int y) {
		for (int i = 0; i < V.size(); i++)
		{
			if (x>= V[i].x && x<= V[i].x + V[i].w && y>= V[i].y && y<= V[i].y + V[i].h)
			{
				return i;
			}
		}
		return -1;
	}

	void blitRootBtn(int i) {
		SDL_Rect cr = { 0, 30 * i, 110, 30 };
		SDL_BlitScaled(images[gameSetting::menuSetting.menuImg::rootBtns], &cr, gameSetting::surface, &this->rootBtnRects[i]);
	}

	void blitSwitch(int hB, int hF) {
		SDL_Rect cr = { this->settingBtnsRects[0].x - 50, 0, this->menuBtnsHeight, this->menuBtnsHeight };
		for (int i = 0; i < this->settingBtnsRects.size(); i++)
		{
			cr.y = this->settingBtnsRects[i].y;
			SDL_BlitScaled(images[gameSetting::menuSetting.menuImg::BG],
				NULL, gameSetting::surface, &cr);
		}
		if (hB != -1)
		{
			cr.y = this->settingBtnsRects[hB].y;
		}
		else
		{
			cr.y = this->settingBtnsRects[this->hardnessSettingBombTemp].y;
		}
		SDL_BlitScaled(images[gameSetting::menuSetting.menuImg::bomb],
			NULL, gameSetting::surface, &cr);
		if (hF != -1)
		{
			cr.y = this->settingBtnsRects[hF + 3].y;
		}
		else
		{
			cr.y = this->settingBtnsRects[this->hardnessSettingFieldTemp + 3].y;
		}
		SDL_BlitScaled(images[gameSetting::menuSetting.menuImg::flag],
			NULL, gameSetting::surface, &cr);

		SDL_UpdateWindowSurface(gameSetting::win);
	}

	void blitWinSettings(bool update) {

		static int v = 0;
		if (v == 0 && !update)
		{
			this->blitMenuBg();

			this->blitSwitch(this->hardnessSettingBombTemp, this->hardnessSettingFieldTemp);

			for (int i = 0; i < this->settingBtnsRects.size(); i++)
			{
				SDL_Rect cr = { 0, 30 * i , 110, 30	};
				SDL_BlitScaled(images[gameSetting::menuSetting.menuImg::menuSettingsBtns],
					&cr, gameSetting::surface, &this->settingBtnsRects[i]);
			}

			this->blitRootBtn(gameSetting::menuSetting.rootBtn::accept);
			this->blitRootBtn(gameSetting::menuSetting.rootBtn::cancel);

			SDL_UpdateWindowSurface(gameSetting::win);
			std::cout << "settings\n";
			v++;
		}
		else if (v > 0 && !update)
		{
			return;
		}
		else if (v > 0 && update)
		{
			v = 0;
			return;
		}
	}


	void blitWinAbout(bool update) {

		static int v = 0;
		if (v == 0 && !update)
		{
			this->blitMenuBg();

			SDL_Rect mr = {
				this->winWidth / 2 - this->menuWidth / 2 + this->PadingTop,
				this->menuY + this->PadingTop,
				this->winWidth,
				this->winHeight
			};
			std::string str = "Классическая игра САПЕР\nРазработа студентом БГТУ 'Военмех' Гранитовым А.С. как курсовая работа\n\n"
				 "GIT: ";
			this->blitTxt(this->font, this->color, str.c_str(), mr);
			str.clear();

			this->blitRootBtn(gameSetting::menuSetting.rootBtn::cancel);
			SDL_UpdateWindowSurface(gameSetting::win);
			v++;
		}
		else if (v > 0 && !update)
		{
			return;
		}
		else if (v > 0 && update)
		{
			v = 0;
			return;
		}
	}


	void setStat(std::vector<std::vector<int>>stat, int statGC) {
		this->stat = stat;
		this->statGC = statGC;
	}

	int list = 0;
	void blitWinStat(bool update) {

		static int v = 0;
		std::cout << v << " vvv\n";
		if (v == 0 && !update)
		{
			this->blitMenuBg();
			SDL_Rect mr = { 
				this->winWidth / 2 - this->menuWidth / 2 + this->PadingTop,
				this->menuY + this->PadingTop,
				this->winWidth,
				this->winHeight
			};
			std::string str ="";
			switch (this->list)
			{
			case gameSetting::difficultG.hLvl::easy:
				str = "всего игр - " + std::to_string(this->statGC) + "	\nМаленькое поле:\nвсего игр|побед|лучшее t|% побед\n"
					"легко\n" + std::to_string(this->stat[0][0]) + "         " + std::to_string(this->stat[0][1]) +
					"         " + std::to_string(this->stat[0][2]) + "         " + std::to_string(
						this->stat[0][0] != 0 ? int(this->stat[0][1]*100 / this->stat[0][0]) : 0
					) + "\n"

					"нормально\n" + std::to_string(this->stat[1][0]) + "         " + std::to_string(this->stat[1][1]) +
					"         " + std::to_string(this->stat[1][2]) + "         " + std::to_string(
						this->stat[1][0] != 0 ? int(this->stat[1][1] * 100 / this->stat[1][0]) : 0
					) + "\n"

					"сложно\n" + std::to_string(this->stat[2][0]) + "         " + std::to_string(this->stat[2][1]) +
					"         " + std::to_string(this->stat[2][2]) + "         " + std::to_string(
						this->stat[2][0] != 0 ? int(this->stat[2][1] * 100 / this->stat[2][0]) : 0
					) + "\n";

				this->blitTxt(this->font, this->color, str.c_str(), mr);
			break;
			case gameSetting::difficultG.hLvl::normal:
				str = "всего игр - " + std::to_string(this->statGC) + "	\nСреднее поле:\nвсего игр|побед|лучшее t|%побед\n"
					"легко\n" + std::to_string(this->stat[3][0]) + "         " + std::to_string(this->stat[3][1]) +
					"         " + std::to_string(this->stat[3][2]) + "         " + std::to_string(
						this->stat[3][0] != 0 ? int(this->stat[3][1] * 100 / this->stat[3][0]) : 0
					) + "\n"

					"нормально\n" + std::to_string(this->stat[4][0]) + "         " + std::to_string(this->stat[4][1]) +
					"         " + std::to_string(this->stat[4][2]) + "         " + std::to_string(
						this->stat[4][0] != 0 ? int(this->stat[4][1] * 100 / this->stat[4][0]) : 0

					) + "\n"
					"сложно\n" + std::to_string(this->stat[5][0]) + "         " + std::to_string(this->stat[5][1]) +
					"         " + std::to_string(this->stat[5][2]) + "         " + std::to_string(
						this->stat[5][0] != 0 ? int(this->stat[5][1] * 100 / this->stat[5][0]) : 0
					) + "\n";
				this->blitTxt(this->font, this->color, str.c_str(), mr);
				break;
			case gameSetting::difficultG.hLvl::hard:
				str = "всего игр - " + std::to_string(this->statGC) + "	\nБольшое поле:\nвсего игр|побед|лучшее t|%побед\n"
					"легко\n" + std::to_string(this->stat[6][0]) + "         " + std::to_string(this->stat[6][1]) +
					"         " + std::to_string(this->stat[6][2]) + "         " + std::to_string(
						this->stat[6][0] != 0 ? int(this->stat[6][1] * 100 / this->stat[6][0]) : 0
					) + "\n"

					"нормально\n" + std::to_string(this->stat[7][0]) + "         " + std::to_string(this->stat[7][1]) +
					"         " + std::to_string(this->stat[7][2]) + "         " + std::to_string(
						this->stat[7][0] != 0 ? int(this->stat[7][1] * 100 / this->stat[7][0]) : 0
					) + "\n"

					"сложно\n" + std::to_string(this->stat[8][0]) + "         " + std::to_string(this->stat[8][1]) +
					"         " + std::to_string(this->stat[8][2]) + "         " + std::to_string(
						this->stat[8][0] != 0 ? int(this->stat[8][1] * 100 / this->stat[8][0]) : 0
					) + "\n";
				this->blitTxt(this->font, this->color, str.c_str(), mr);
				str.clear();
				break;
			default:
				this->list = -1;
				break;
			}
			this->blitRootBtn(gameSetting::menuSetting.rootBtn::cancel);

			SDL_UpdateWindowSurface(gameSetting::win);
			std::cout << "ttfStatistic\n";
			v++;
		}
		else if (v > 0 && !update)
		{
			return;
		}
		else if (v > 0 && update)
		{
			v = 0;
			return;
		}
	}
};


