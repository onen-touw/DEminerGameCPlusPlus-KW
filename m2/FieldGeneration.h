#pragma once
#include "imagesClass.h"
#include "setting.h"
//using settingGame::Surface;
//using settingGame::win;


class FieldGeneration :
    public imagesClass
{
private:

	short int bombCount = 0;

	std::vector <std::vector<cell_values>> field_;


public:

	FieldGeneration() {}
	~FieldGeneration()
	{
		field_.clear();
	}

	///
	void createField() {
		field_.clear();
		field_.resize(gameSetting::difficultG.gH);
		for (int i = 0; i < gameSetting::difficultG.gH; i++)
		{
			field_[i].resize(gameSetting::difficultG.gW);
		}
	}

	///генерация матрицы ячеек
	void generateField() {
		
		int y = gameSetting::winObjSize.HeaderHeight;

		for (int i = 1; i < field_.size()-1; i++)
		{
			int x = 0;
			for (int j = 1; j < field_[i].size()-1; j++)
			{
				
					field_[i][j].x += x;
					field_[i][j].y += y;
					x += gameSetting::winObjSize.cellSize;
				
				field_[i][j].i = i;
				field_[i][j].j = j;
			}
			
				y += gameSetting::winObjSize.cellSize;
			
		}
	}

	///ф-ция вовзрата кол-ва бомб
	short getBombCount() {
		return this->bombCount;
	}
	short& getBombCountLink() { return this->bombCount; }

	void generateBombCouont() {
		this->bombCount = this->field_.size() * this->field_[0].size() / gameSetting::difficultG.bombDensity;
	}

	///случайное распределение бомб
	void generateRandomBomb() {
		int w = this->field_.size() - 2;
		int h = this->field_[0].size() - 2;

		srand(time(0));

		for (int i = 0; i < this->bombCount; i++)
		{
			int x = rand() % h + 1;
			int y = rand() % w + 1;

			if (this->field_[x][y].bomb) //проверка есть ли бомба в ячейке
			{
				i--;
			}
			else
			{
				this->field_[x][y].bomb = true;
			}
		}
	}


	///возвращает ветор поля
	std::vector<std::vector<cell_values>>&getVector() { return this->field_; }

	//создание поля из SAVE
	void setFieldFromSave(std::vector<std::vector<cell_values>> fieldFrom) {
		this->field_.clear();
		this->field_ = fieldFrom;
		for (int i = 0; i < fieldFrom.size(); i++)
		{
			for (int j = 0; j < fieldFrom[0].size(); j++)
			{
				std::cout <<field_[i][j].bomb
					<< field_[i][j].open
					<< field_[i][j].flag
					<< fieldFrom[i][j].bmb_near
					<< field_[i][j].question
					<< " "; 
			}
			std::cout << "\n";
		}
	}





	//возвращает ячейку i j
	cell_values getCell(int i, int j) {
		return field_[i][j];
	}

	///ф-ция установки флага
	void setFlag(int i, int j) {
		if (field_[i][j].flag == 0)
		{
			field_[i][j].flag = 1;
		}
		else
		{
			field_[i][j].flag = 0;
		}
		return;
	}

	///ф-ция установки вопроса
	void setQuestion(int i, int j) {
		if (field_[i][j].question == 0)
		{
			field_[i][j].question = 1;
		}
		else
		{
			field_[i][j].question = 0;
		}
		return;
	}


	/*///установка бомбы в ячейку i j
	void setBomb(position pos) {
		field_[pos.i][pos.j].bomb = true;
		return;
	}*/

	///установка значения ОТКРЫТО в ячейку i j
	void setOpen(position pos) {
		field_[pos.i][pos.j].open = true;
		return;
	}


	///===================================
	///установка номера в ячейку если она номер(находится рядом с бомбой)
	void setBmbCountNearCell(position pos, int count) {
		field_[pos.i][pos.j].bmb_near = count;
		return;
	}
	//поиск бомб вокруг пустой ячейки
	//возвращает кол-во бомб вокруг ячейки i j
	int roundSearch(int i, int j) {
		int count = 0;
		if (!field_[i][j].bomb)
		{
			short int mas[] = {
				field_[i - 1][j - 1].bomb,
				field_[i - 1][j + 1].bomb,
				field_[i - 1][j].bomb,
				field_[i][j + 1].bomb,
				field_[i + 1][j + 1].bomb,
				field_[i + 1][j].bomb,
				field_[i + 1][j - 1].bomb,
				field_[i][j - 1].bomb,
			};
			for (int i = 0; i < 8; i++)
			{
				if (mas[i] == 1)
				{
					count++;
				}
			}
		}
		return count;
	}

	//вставляем значение ф-ции search_bobm в ячейку i j
	void searchNearBomb() {
		for (int i = 1; i < this->field_.size() - 1; i++)
		{
			for (int j = 1; j < this->field_[0].size() - 1; j++)
			{
				if (!field_[i][j].bomb)
				{
					setBmbCountNearCell({ (short)i, (short)j }, roundSearch(i, j));
				}
			}
		}
	}
	///===================================


	void BLIT(position pos, short img) {
		SDL_Rect mr = { field_[pos.i][pos.j].x, field_[pos.i][pos.j].y, gameSetting::winObjSize.cellSize, gameSetting::winObjSize.cellSize };
		SDL_BlitScaled(images[img], NULL, gameSetting::surface, &mr);
	}

	//отрисовка номера ячейки(если это ячейка с числом)
	void blitNumber(position pos, int num) {

		if (num > 0 && num < 9)
		{
			SDL_Rect mr = { field_[pos.i][pos.j].x, field_[pos.i][pos.j].y, gameSetting::winObjSize.cellSize, gameSetting::winObjSize.cellSize };
			SDL_Rect cr = { (num - 1) * gameSetting::fieldSetting.numberCropSize, 0 ,gameSetting::fieldSetting.numberCropSize, gameSetting::fieldSetting.numberCropSize };
			SDL_BlitScaled(images[gameSetting::fieldSetting.gameImg::numbers], &cr, gameSetting::surface, &mr);
		}
		else
		{
			return;
		}
	}



	////отрисовка пустого поля h на w
	//void BLIT_FIELD() {
	//	for (int i = 1; i < field_.size() - 1; i++)
	//	{
	//		for (int j = 1; j < field_[0].size() - 1; j++)
	//		{
	//			SDL_Rect cell_rect = { field_[i][j].x ,field_[i][j].y ,size, size };
	//			SDL_BlitScaled(arr[0], NULL, Surface, &cell_rect);	///
	//		}
	//	}
	//}

	//отрисовка проигранного поля h на w
	//void BLIT_GAME_LOSE_FIELD() {
	//	for (int i = 1; i < field_.size() - 1; i++)
	//	{
	//		for (int j = 1; j < field_[0].size() - 1; j++)
	//		{
	//			if (field_[i][j].bomb)
	//			{
	//				BLIT(i, j, gameImgs::bombCell);
	//			}
	//			else if (field_[i][j].bmb_near)
	//			{
	//				BLIT_NUMBER(i, j, field_[i][j].bmb_near);
	//			}
	//			/*else if (!field_[i][j].bomb && field_[i][j].flag)
	//			{
	//				BLIT_CELL_E_BOMB(i, j);
	//			}*/
	//			else
	//			{
	//				BLIT(i, j, gameImgs::openCell);
	//			}
	//		}
	//	}
	//}

	void bliField() {
		for (short i = 1; i < field_.size() - 1; i++)
		{
			for (short j = 1; j < field_[0].size() - 1; j++)
			{
				if (field_[i][j].open)
				{
					if (field_[i][j].bmb_near) {
						this->blitNumber({ i, j }, this->field_[i][j].bmb_near);
					}

					else if (field_[i][j].bomb) {
						this->BLIT({ i,j }, gameSetting::fieldSetting.gameImg::bomb);
					}
					else {
						this->BLIT({ i,j }, gameSetting::fieldSetting.gameImg::openCell);
					}
				}
				else{
					if (field_[i][j].flag) {
						this->BLIT({ i,j }, gameSetting::fieldSetting.gameImg::flag);
					}
					else if (field_[i][j].question) {
						this->BLIT({ i,j }, gameSetting::fieldSetting.gameImg::question);
					}
					else
					{
						this->BLIT({ i,j }, gameSetting::fieldSetting.gameImg::cell);
					}
				}
			}
		}
		SDL_UpdateWindowSurface(gameSetting::win);
	}

	

	//поиск ячейки по координатам (+ проверка на нахождение курсора в игровой области)
	position findCell(position pos) {
		// параметры ограничения поля прописана от 0
		if (pos.i >= 0 && pos.i <= (field_.size() * gameSetting::winObjSize.cellSize) && pos.j >= 0
			&& pos.j <= field_[0].size() * gameSetting::winObjSize.cellSize)
		{
			for (int i = 1; i < field_.size() - 1; i++)
			{
				for (int j = 1; j < field_[0].size() - 1; j++)
				{
					if (pos.i > field_[i][j].x && pos.i < field_[i][j].x + gameSetting::winObjSize.cellSize
						&& pos.j > field_[i][j].y && pos.j < field_[i][j].y + gameSetting::winObjSize.cellSize)
					{
						return { field_[i][j].i, field_[i][j].j };
					}
				}
			}
		}
		return {-1, -1};
	}

	//дебаг
	void debug(int deb) {
		for (int i = 0; i < this->field_.size(); i++)
		{
			for (int j = 0; j < this->field_[0].size(); j++)
			{
				if (deb == 1)
				{
					std::cout << "(" << field_[i][j].i << " " << field_[i][j].j << ") ";
				}
				else if (deb == 2)
				{
					std::cout << field_[i][j].bomb
						<< field_[i][j].open << field_[i][j].flag << field_[i][j].bmb_near << " ";
				}
				else if (deb == 4)
				{
					std::cout << field_[i][j].x << "-" << field_[i][j].y << " ";
				}

				else if (deb == 3)
				{
					if (field_[i][j].bomb)
					{
						std::cout << "+ ";
					}
					else
					{
						std::cout << field_[i][j].bmb_near << " ";
					}
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	


	

	
};

