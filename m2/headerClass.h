#pragma once

//#include"settings.h"
#include"imagesClass.h"
#include<string>


class headerClass : public imagesClass
{

private:
	Uint32 timer = 0;
	Uint32 timerPoint = 0;
	Uint32 additionTime = 0;
	std::string gTime = "000";
	std::string timeTemp;
	std::string timeTemp2;

	std::string bmbCount = "000";
	std::string bmbCTemp = "000";

	int headerPadingLeft = 0;
	int headerPadingTop = 0;
	int numHeight = 40;
	int numWidth = 30;
	int winWidth = gameSetting::winObjSize.winWIDTH;
public:

	headerClass() {
		this-> headerPadingLeft =  gameSetting::menuSetting.menuPadingLeft;
		this->headerPadingTop =  gameSetting::menuSetting.menuPaddingTop;
	}

	~headerClass()
	{

	}

	void updateSizes() {
		this->winWidth = gameSetting::winObjSize.winWIDTH;
	}

	void resetTimerAndCounter() {
		this->timer = 0;
		this->bmbCount = "000";
		this->bmbCTemp = "000";
		this->gTime = "000";
		this->timerPoint = 0;
	}

	///start timer point
	void setGTime() {
		timerPoint = SDL_GetTicks();
	}
	int getTime() { return this->timer; }

	///счет времени
	Uint32 gTimer() {
		if (timerPoint != 0)
		{
			timer = ((SDL_GetTicks() - timerPoint) / 1000) + this->additionTime;
			if (timer >= 999)
			{
				timer = 999;
			}
		}
		return timer;
	}

	Uint32& getAdditionTime() { return this->additionTime; }
	void resetAdditTime() {
		this->additionTime = 0;
	}

	///отрисовка таймера + оптимизация
	void blitGTime() {
		if (timer != 0)
		{
			timeTemp = std::to_string(timer);
			if (timeTemp.size() == 1)
			{
				gTime[2] = timeTemp[0];
			}
			else if (timeTemp.size() == 2)
			{
				gTime[1] = timeTemp[0];
				gTime[2] = timeTemp[1];
			}
			else
			{
				gTime = timeTemp;
			}
		}

		//оптимизация отрисовки
		if (gTime != timeTemp2)
		{
			timeTemp2 = gTime;
			for (int i = 0; i < gTime.size(); i++)
			{
				SDL_Rect motion_rect = {this->headerPadingLeft + i * this->numWidth, this->headerPadingTop , this->numWidth, this->numHeight};
				SDL_Rect crop_rect = { 171 * (gTime[i] - '0'), 0 , 171, 300 };
				SDL_BlitScaled(this->images[gameSetting::menuSetting.headerImg::numberss],
					&crop_rect, gameSetting::surface, &motion_rect);
			}
			SDL_UpdateWindowSurface(gameSetting::win);
		}

	}


	void bombCounter(int fc, int bc) {
		bmbCTemp = std::to_string(abs(bc - fc));
		std::cout << bmbCTemp << " << real Count of bomb\n";
		if (bmbCTemp.size() == 1)
		{
			bmbCount = "000";
			bmbCount[2] = bmbCTemp[0];
		}
		else if (bmbCTemp.size() == 2)
		{
			bmbCount = "000";
			bmbCount[1] = bmbCTemp[0];
			bmbCount[2] = bmbCTemp[1];
		}
		else {
			bmbCount = bmbCTemp;
		}

		for (int i = 0; i < bmbCount.size(); i++)
		{
			SDL_Rect motion_rect = { this->winWidth - this->numWidth*3 - this->headerPadingLeft + i * this->numWidth, 
				this->headerPadingTop , this->numWidth, this->numHeight };
			SDL_Rect crop_rect = { 171 * (bmbCount[i] - '0'), 0 , 171, 300 };
			SDL_BlitScaled(this->images[gameSetting::menuSetting.headerImg::numberss], &crop_rect, gameSetting::surface, &motion_rect);
		}
		SDL_UpdateWindowSurface(gameSetting::win);
	}

	void blitSmile(int smileIMG) {
		SDL_Rect motion_rect = { this->winWidth / 2 - this->numHeight/2, this->headerPadingTop , this->numHeight, this->numHeight };
		SDL_BlitScaled(this->images[smileIMG], NULL, gameSetting::surface, &motion_rect);
		SDL_UpdateWindowSurface(gameSetting::win);
	}


	void blitHeader(int flagCount, int underFlagCount) {
		SDL_Rect mr = { 0, 0, gameSetting::winObjSize.winWIDTH, gameSetting::winObjSize.HeaderHeight};
		SDL_BlitScaled(this->images[gameSetting::menuSetting.headerImg::headerBg],
			NULL, gameSetting::surface, &mr);
		this->blitGTime();
		this->bombCounter(flagCount, underFlagCount);
		this->blitSmile(gameSetting::menuSetting.headerImg::smile);
	}


	


};