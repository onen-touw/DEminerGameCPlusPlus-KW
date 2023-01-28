#pragma once

#include"baseGameClass.h"
#include"FieldGeneration.h"
#include"mouseAction.h"

#include "saveGame.h"
//#include"mAtest.h"


#include"headerClass.h"
#include "menuClass.h"

class gameplayClass
{
private:
	baseGameClass bcTest;
	FieldGeneration fTest;
	mouseAction mActionsTest;
	headerClass header;
	menuClass menu;
	saveGame save;

	int winStatusI = -1;

	bool gResult = false;
	bool fClick = false;


	bool game = true;



	int cursor_X = 0, cursor_Y = 0;

public:
	gameplayClass() {

		fTest.setImgVectSize(gameSetting::fieldSetting.gameImg::gameImgTOTAL);
		fTest.loadImg("./images/gameImages/MainCell.png", gameSetting::fieldSetting.gameImg::cell);
		fTest.loadImg("./images/gameImages/openCell.png", gameSetting::fieldSetting.gameImg::openCell);
		fTest.loadImg("./images/gameImages/cell_bomb.png", gameSetting::fieldSetting.gameImg::bomb);
		fTest.loadImg("./images/gameImages/cell_flag.png", gameSetting::fieldSetting.gameImg::flag);
		fTest.loadImg("./images/gameImages/cell_question.png", gameSetting::fieldSetting.gameImg::question);
		fTest.loadImg("./images/gameImages/cells_number.png", gameSetting::fieldSetting.gameImg::numbers);
		
		header.setImgVectSize(gameSetting::menuSetting.headerImg::headerImgTOTAL);
		header.loadImg("./images/menuImges/BBG.png", gameSetting::menuSetting.headerImg::headerBg);
		header.loadImg("./images/menuImges/numbers_red.png", gameSetting::menuSetting.headerImg::numberss);
		header.loadImg("./images/menuImges/menuSmile.png", gameSetting::menuSetting.headerImg::smile);
		header.loadImg("./images/menuImges/xsign.png", gameSetting::menuSetting.headerImg::xSign);
		header.loadImg("./images/menuImges/winSmile.png", gameSetting::menuSetting.headerImg::winSign);
		header.loadImg("./images/menuImges/die.png", gameSetting::menuSetting.headerImg::loseSign);


		menu.setImgVectSize(gameSetting::menuSetting.menuImg::imgMenuTOTAL);
		menu.loadImg("./images/menuImges/BBG.png", gameSetting::menuSetting.menuImg::BG);
		menu.loadImg("./images/menuImges/mainBTNS.png", gameSetting::menuSetting.menuImg::menuFirstLvlBtns);
		menu.loadImg("./images/menuImges/settBt.png", gameSetting::menuSetting.menuImg::menuSettingsBtns);
		menu.loadImg("./images/menuImges/AcBtn.png", gameSetting::menuSetting.menuImg::rootBtns);
		menu.loadImg("./images/gameImages/cell_bomb.png", gameSetting::menuSetting.menuImg::bomb);
		menu.loadImg("./images/gameImages/cell_flag.png", gameSetting::menuSetting.menuImg::flag);

	}
	~gameplayClass()
	{

	}

	void generateGame() {
		save.DataOpen();

		if (!this->save.LastGameOpen(this->fTest.getVector(),
			this->fTest.getBombCountLink(),
			this->mActionsTest.getUnderFlagBombCounterLink(),
			this->header.getAdditionTime()
		))
		{
			fTest.createField();
			fTest.generateBombCouont();
			fTest.generateRandomBomb();
			fTest.searchNearBomb();

		}
		else
		{
			this->bcTest.rebuildWin();

		}

		this->header.updateSizes();
		this->menu.updateSizes();
		this->menu.setBtnsRects();

		fTest.generateField();

		this->gResult = false;
		this->fClick = false;

		fTest.bliField();
		header.blitHeader(fTest.getBombCount(), mActionsTest.getUnderFlagBombCounter());
		fTest.debug(3);
		this-> winStatusI = -1;

	}


	void startGame() {
		SDL_Event event;
		this->generateGame();

		while (this->game) {

			while (SDL_PollEvent(&event) || this->game)
			{
				if (!this->gResult && this->fClick)
				{
					this->header.gTimer();
					this->header.blitGTime();
				}
				
				if (this->gResult)
				{
					if (this->winStatusI == gameStatus::win)
					{
						header.blitSmile(gameSetting::menuSetting.headerImg::winSign);

					}
					else
					{
						header.blitSmile(gameSetting::menuSetting.headerImg::loseSign);
					}
				}


				if (event.type == SDL_QUIT)//отслеживание закрытия окна через кнопку "Крест"
				{
					if (!this->gResult)
					{
						this->save.LastGameSave(
							this->fTest.getVector(),
							gameSetting::hardnessField, 
							gameSetting::hardnessBomb, 
							this->header.getTime(), 
							this->fTest.getBombCount(), 
							this->mActionsTest.getUnderFlagBombCounter()
						);
					}

					this->game = false;
					return;
				}


				else if (event.button.button == SDL_BUTTON_RIGHT && event.type == SDL_MOUSEBUTTONUP && !this->gResult && !this->menu.getMenuFlag())
				{
					SDL_GetMouseState(&cursor_X, &cursor_Y);
					position pos = fTest.findCell(this->cursor_X, this->cursor_Y);
					if (pos.i > -1 && pos.j > -1){

						this->mActionsTest.RIGHT_CLICK(this->fTest.getVector(), pos.i, pos.j);

						this->header.bombCounter(this->mActionsTest.getFlagCount(), this->fTest.getBombCount());

						if (this->mActionsTest.getFlagCount() == this->fTest.getBombCount())
						{
							if (this->mActionsTest.getUnderFlagBombCounter() == this->fTest.getBombCount())
							{
								std::cout << "WINWINWINWINWINWINW\n";
								this->save.DataSave(gameSetting::hardnessField, gameSetting::hardnessBomb, gameStatus::win, this->header.getTime());
								this->mActionsTest.resetFlagsCounters();
								this->header.resetAdditTime();
								this->gResult = true;
								this->winStatusI = gameStatus::win;
							}
							else
							{
								std::cout << "ERROR ERROR ERROR ERROR ERROR \n";
								this->header.blitSmile(gameSetting::menuSetting.headerImg::xSign);

							}
						}
						else if(this->fTest.getBombCount() > this->mActionsTest.getFlagCount())
						{
							this->header.blitSmile(gameSetting::menuSetting.headerImg::smile);

						}
						fTest.bliField();
					}
				}
				else if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
				{
					SDL_GetMouseState(&cursor_X, &cursor_Y);

					if (cursor_Y <= gameSetting::winObjSize.HeaderHeight)
					{
						this->menu.blitWinMenu(false);
					}
					else {
						if (!this->fClick && !this->menu.getMenuFlag())
						{
							this->fClick = true;

							///timerStart
							this->header.setGTime();
						}

						if (!menu.getMenuFlag() && !this->gResult)
						{
							position pos = this->fTest.findCell(this->cursor_X, this->cursor_Y);
							if (pos.i > -1 && pos.j > -1)
							{
								if (!this->mActionsTest.LEFT_CLICK(fTest.getVector(), pos.i, pos.j))
								{
									std::cout << " LOSE LOSE LOSE LOSE LOSE\n";
									this->save.DataSave(gameSetting::hardnessField, gameSetting::hardnessBomb, gameStatus::lose, this->header.getTime());
									this->mActionsTest.resetFlagsCounters();
									this->header.resetAdditTime();
									this->winStatusI = gameStatus::lose;

									this->gResult = true;
								}
								this->fTest.bliField();
								this->mActionsTest.BLIT_AFTER_SEARCH(fTest.getVector());
							}
						}
						else if (this->menu.getMenuFlag() && this->menu.getSecondLvl() == -1)
						{
							switch (this->menu.btnParse(this->menu.getMainBtnV(), cursor_X, cursor_Y))
							{
							case gameSetting::menuSetting.menuPuncts::statistic:
								menu.menuSetSecondLvl(gameSetting::menuSetting.menuPuncts::statistic);
								this->save.DataOpen();
								this->menu.list = 0;
								this->menu.setStat(this->save.getStat(), this->save.getGameCount());
								this->menu.blitWinStat(false);
								std::cout << "stat\n";
								break;
							case gameSetting::menuSetting.menuPuncts::settings:
								this->menu.menuSetSecondLvl(gameSetting::menuSetting.menuPuncts::settings);
								this->menu.blitWinSettings(false);
								std::cout << "sett\n";
								break;
							case gameSetting::menuSetting.menuPuncts::about:
								this->menu.menuSetSecondLvl(gameSetting::menuSetting.menuPuncts::about);
								this->menu.blitWinAbout(false);
								std::cout << "ab\n";
								break;
							case gameSetting::menuSetting.menuPuncts::quitBtn:
								std::cout << "qq\n";
								if (!this->gResult)
								{
									this->save.LastGameSave(
										this->fTest.getVector(),
										gameSetting::hardnessField,
										gameSetting::hardnessBomb,
										this->header.getTime(),
										this->fTest.getBombCount(),
										this->mActionsTest.getUnderFlagBombCounter()
									);
								}
								return;
								break;
							case gameSetting::menuSetting.menuPuncts::cancelBtn:
								this->menu.toggleFlag();
								this->menu.blitWinMenu(true);
								this->fTest.bliField();
								SDL_UpdateWindowSurface(gameSetting::win);
								std::cout << "cc\n";
								break;
							default:
								break;
							}
						}
						else if(this->menu.getMenuFlag() && this->menu.getSecondLvl() != -1)
						{
							switch (this->menu.getSecondLvl())
							{
							case gameSetting::menuSetting.menuPuncts::statistic:
								if (this->menu.btnParse(this->menu.getRootBtnV(), cursor_X, cursor_Y) == gameSetting::menuSetting.rootBtn::cancel)
								{
									this->menu.menuSetSecondLvl(-1);
									this->menu.blitWinMenu(true);
									this->menu.blitWinMenu(false);
									this->menu.blitWinStat(true);
									SDL_UpdateWindowSurface(gameSetting::win);
								}
								else
								{
									this->menu.list++;
									this->save.DataOpen();

									this->menu.setStat(this->save.getStat(), this->save.getGameCount());
									this->menu.blitWinStat(true);
									this->menu.blitWinStat(false);

								}
								break;
							case gameSetting::menuSetting.menuPuncts::settings:
								switch (this->menu.btnParse(menu.getSettingBtnV(), cursor_X, cursor_Y))
								{
								case gameSetting::menuSetting.menuSettingPuncts::easyBmb:
									menu.setHardnessB(gameSetting::difficultG.easy);
									menu.blitSwitch(gameSetting::difficultG.easy, -1);
									std::cout << "111\n";

									break;
								case gameSetting::menuSetting.menuSettingPuncts::normalBmb:
									menu.setHardnessB(gameSetting::difficultG.normal);
									menu.blitSwitch(gameSetting::difficultG.normal, -1);
									std::cout << "222\n";
									break;
								case gameSetting::menuSetting.menuSettingPuncts::hardBmb:
									menu.setHardnessB(gameSetting::difficultG.hard);
									menu.blitSwitch(gameSetting::difficultG.hard, -1);
									std::cout << "333\n";
									break;
								case gameSetting::menuSetting.menuSettingPuncts::smallF:
									menu.setHardnessF(gameSetting::difficultG.easy);
									menu.blitSwitch(-1, gameSetting::difficultG.easy);

									break;
								case gameSetting::menuSetting.menuSettingPuncts::mediumF:
									menu.setHardnessF(gameSetting::difficultG.normal);
									menu.blitSwitch(-1, gameSetting::difficultG.normal);
									break;
								case gameSetting::menuSetting.menuSettingPuncts::largeF:
									menu.setHardnessF(gameSetting::difficultG.hard);
									menu.blitSwitch(-1, gameSetting::difficultG.hard);
									break;
								default:

									switch (menu.btnParse(menu.getRootBtnV(), cursor_X, cursor_Y))
									{
									case gameSetting::menuSetting.rootBtn::accept:
										menu.updateHardSetting();
										menu.blitWinSettings(true);
										menu.blitWinMenu(true);
										menu.menuSetSecondLvl(-1);
										menu.toggleFlag();
										header.resetTimerAndCounter();
										header.resetAdditTime();
										gameSetting::difficultG.updateFieldSize(gameSetting::hardnessField);
										gameSetting::difficultG.updateBombDensity(gameSetting::hardnessBomb);



										if (bcTest.rebuildWin()) {
											this->generateGame();
										}
										else return;
										
										break;
									case gameSetting::menuSetting.rootBtn::cancel:
										std::cout << "888\n";
										menu.setHardnessB(gameSetting::hardnessBomb);
										menu.setHardnessF(gameSetting::hardnessField);
										menu.menuSetSecondLvl(-1);
										menu.blitWinMenu(true);
										menu.blitWinMenu(false);
										menu.blitWinSettings(true);
										SDL_UpdateWindowSurface(gameSetting::win);

										break;
									default:
										break;
									}
									break;
								}
								break;
							case gameSetting::menuSetting.menuPuncts::about:
								if (this->menu.btnParse(menu.getRootBtnV(), cursor_X, cursor_Y) == gameSetting::menuSetting.rootBtn::cancel)
								{
									menu.menuSetSecondLvl(-1);
									menu.blitWinMenu(true);
									menu.blitWinMenu(false);
									menu.blitWinAbout(true);
									SDL_UpdateWindowSurface(gameSetting::win);
								}


								break;
							default:
								break;
							}
						}
					}
				}
				SDL_Delay(1000 / 60);

			}

		}
		return;
	}
};