#pragma once
#include "FieldGeneration.h"

class mouseAction :
    public FieldGeneration
{

private:
	short int underFlagBombCount = 0;
	short int flaCount = 0;

public:

	void test(short i, short j, std::vector<std::vector<cell_values>>& V) {
		this->SEARCH_AROUND(i, j, V);
		this->BLIT_AFTER_SEARCH(V);
	}

	void SEARCH_AROUND(short i, short j, std::vector<std::vector<cell_values>>& V) {
		//cout << "==========SEARCH_AROUND_WAS_STARTED==========" << endl;

		if (i < 1 || i > V.size() - 2 || j < 1 || j > V[0].size() - 2) //если край пол€
		{
			return;
		}

		if (V[i][j].open) //если €чейка уже открыта
		{
			return;
		}

		if (V[i][j].bmb_near != 0) //если €чейка не имеет мину но находитс€ р€дом с ней(ними)
		{
			V[i][j].open = true;
			return;
		}

		if (!V[i][j].open && !V[i][j].bomb) //если это не бомба и €чейка закрыта открываем ее и идем в следующие
		{
			V[i][j].open = true;
			//рекурси€
			SEARCH_AROUND(i - 1, j, V);
			SEARCH_AROUND(i + 1, j, V);
			SEARCH_AROUND(i, j - 1, V);
			SEARCH_AROUND(i, j + 1, V);

		
		}
		else
		{
			return;
		}
		//cout << "==========SEARCH_AROUND_READY==========" << endl;
		return;
	}

	void BLIT_AFTER_SEARCH(std::vector<std::vector<cell_values>>&V) {
		for (short i = 1; i < V.size() - 1; i++)
		{
			for (short j = 1; j < V[i].size() - 1; j++)
			{
				if (V[i][j].open && !V[i][j].bmb_near)
				{
					if (V[(i + 1)][(j + 1)].bmb_near)
					{
						V[(i + 1)][(j + 1)].open = true;
					}
					if (V[(i + 1)][(j - 1)].bmb_near)
					{
						V[(i + 1)][(j - 1)].open = true;
					}
					if (V[(i - 1)][(j - 1)].bmb_near)
					{
						V[(i - 1)][(j - 1)].open = true;
					}
					if (V[(i - 1)][(j + 1)].bmb_near)
					{
						V[(i - 1)][(j + 1)].open = true;
					}
				}
			}
		}
		return;
	}



	short int getFlagCount() { return this->flaCount; }
	short int getUnderFlagBombCounter() { return this->underFlagBombCount; }
	short& getUnderFlagBombCounterLink() { return this->underFlagBombCount; }

	////дебаг
	//void DEBUG(std::vector<std::vector<cell_values>>field) {
	//	//cout << "==============DEBUG_GAME_MAIN_CLASS====================" << endl;
	//	for (int i = 0; i < field.size(); i++)
	//	{
	//		for (int j = 0; j < field[i].size(); j++)
	//		{
	//			if (field[i][j].bomb)
	//			{
	//				std::cout << "x ";
	//			}
	//			else if (field[i][j].bmb_near)
	//			{
	//				std::cout << field[i][j].bmb_near << " ";
	//			}
	//			else if (field[i][j].open)
	//			{
	//				std::cout << "0 ";
	//			}
	//			else if (field[i][j].open == 0)
	//			{
	//				std::cout << "- ";
	//			}
	//			else if (field[i][j].open == 1 && field[i][j].bmb_near > 0)
	//			{
	//				std::cout << "& ";
	//			}
	//		}
	//		std::cout << std::endl;
	//	}
	//	//cout << "==============DEBUG_GAME_MAIN_CLASS====================" << endl;
	//}

	//возвращает кол-во флагов вокруг €чейки i j если она не бомба
	bool ROUND_OPEN_ROUND_SEARCH_FLAG(int i, int j, std::vector<std::vector<cell_values>>&V) {
		int count = 0;
		std::vector<cell_values> mas = {
			V[i - 1][j - 1],
			V[i - 1][j + 1],
			V[i - 1][j],
			V[i][j + 1],
			V[i + 1][j + 1],
			V[i + 1][j - 1],
			V[i + 1][j],
			V[i][j - 1],
		};
		for (int k = 0; k < mas.size(); k++)
		{
			if (mas[k].flag)
			{
				count++;
			}
			if (mas[k].question)
			{
				mas.clear();
				return true;
			}
		}

		if (count == V[i][j].bmb_near)
		{
			for (int k = 0; k < mas.size(); k++)
			{
				if (!mas[k].flag)
				{
					if (mas[k].i > 0 && mas[k].i < V.size() - 1 && mas[k].j > 0 && mas[k].j < V[0].size() - 1)
					{
						V[mas[k].i][mas[k].j].open = true;

						if (!V[mas[k].i][mas[k].j].bomb)
						{
							if (V[mas[k].i][mas[k].j].bmb_near == 0) {

								this->SEARCH_AROUND(mas[k].i, mas[k].j, V);
								this->BLIT_AFTER_SEARCH(V);
								V[mas[k].i][mas[k].j].open = true;
							}
							else
							{
								V[mas[k].i][mas[k].j].open = true;

							}
						}
						else
						{

							mas.clear();
							return false;
						}
					}
				}
			}
		}
		mas.clear();
		return true;
	}

	////установка флага в €чейку i j с подсчетом количества найденых мин(проверка правой кнопки)
	void RIGHT_CLICK(std::vector<std::vector<cell_values>>&V, int i, int j) {
		if (!V[i][j].open) //проверка состо€ни€ €чейки 
		{
			std::cout << "JJJJJ\n";

			if (!V[i][j].flag && !V[i][j].question) // флага нет
			{
				V[i][j].flag = true;
				this->flaCount++;
				if (V[i][j].bomb)
				{
					this->underFlagBombCount++;
				}
				return;
			}

			else if (V[i][j].flag)		// если флаг 
			{
				V[i][j].flag = false;
				V[i][j].question = true;
				this->flaCount--;
				if (V[i][j].bomb)
				{
					this->underFlagBombCount--;
				}
				return;
			}

			else if (V[i][j].question)
			{
				V[i][j].question = false;
				return;
			}
		}
		return;
	}

	//// проверка левой кнопки мыши
	bool LEFT_CLICK(std::vector<std::vector<cell_values>>&V, int i, int j) {

		//делигирование условий
		if (V[i][j].bomb)
		{
			if (!V[i][j].flag && !V[i][j].question)
			{
				V[i][j].open = true;
				std::cout << "you lose " << std::endl;
				return false;
			}
		}
		else
		{
			if (V[i][j].open)
			{
				/*if (V[i][j].bmb_near>0)
				{
					if (!ROUND_OPEN_ROUND_SEARCH_FLAG(i, j, V))
					{
						V[i][j].open = true;
						std::cout << "you lose " << std::endl;
						return false;
					}
					else return true;
				}
				else return true;*/
			}
			else
			{
				if (!V[i][j].flag && !V[i][j].question)
				{
					if (V[i][j].bmb_near > 0)
					{
						V[i][j].open = true;
						return true;
					}
					else 
					{

						 this->SEARCH_AROUND(i, j, V);
						this->BLIT_AFTER_SEARCH(V);
						return true;
					}
				}
			}
		}
		return true;
	}



	void resetFlagsCounters() {
		this->flaCount = 0;
		this->underFlagBombCount = 0;
	}

};

