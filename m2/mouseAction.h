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

	std::vector<cell_values>arCell(int i,int j, std::vector<std::vector<cell_values>>& V) {
		std::vector<cell_values>tempDc;
		if (i>0 && j >0 && i < V.size() && j < V[0].size())
		{
			if (!V[i - 1][j - 1].open)
			{
				V[i - 1][j - 1].open = true;
				tempDc.push_back(V[i - 1][j - 1]);
			}
		}
		if (i > 0 && j > 0 && i < V.size() && j < V[0].size())
		{
			if (!V[i - 1][j + 1].open)
			{
				V[i - 1][j + 1].open = true;
				tempDc.push_back(V[i - 1][j + 1]);
			}
		}
		if (i > 0 && j > 0 && i < V.size() && j < V[0].size())
		{
			if (!V[i - 1][j].open)
			{
				V[i - 1][j].open = true;
				tempDc.push_back(V[i - 1][j]);
			}
		}
		if (i > 0 && j > 0 && i < V.size() && j < V[0].size())
		{
			if (!V[i][j + 1].open)
			{
				V[i][j + 1].open = true;
				tempDc.push_back(V[i][j + 1]);
			}
		}

		if (i > 0 && j > 0 && i < V.size() && j < V[0].size())
		{
			if (!V[i + 1][j + 1].open)
			{
				V[i + 1][j + 1].open = true;
				tempDc.push_back(V[i + 1][j + 1]);
			}
		}
		if (i > 0 && j > 0 && i < V.size() && j < V[0].size())
		{
			if (!V[i + 1][j - 1].open)
			{
				V[i + 1][j - 1].open = true;
				tempDc.push_back(V[i + 1][j - 1]);
			}
		}
		if (i > 0 && j > 0 && i < V.size() && j < V[0].size())
		{
			if (!V[i + 1][j].open)
			{
				V[i + 1][j].open = true;
				tempDc.push_back(V[i + 1][j]);
			}
		}
		if (i > 0 && j > 0 && i < V.size() && j < V[0].size())
		{
			if (!V[i][j - 1].open)
			{
				V[i][j - 1].open = true;
				tempDc.push_back(V[i][j - 1]);
			}
		}

		return tempDc;
	}


	void SEARCH_AROUND2(int i, int j, std::vector<std::vector<cell_values>>& V) {

		if (V[i][j].open )
		{
			return;
		}
		else if (V[i][j].bmb_near)
		{
			V[i][j].open = true;
			return;
		}
		else
		{
			std::vector<cell_values>tempDc;
			std::vector<cell_values>tempDc2;
			std::vector<cell_values> Dc;
		
			tempDc = arCell(i, j, V);

		
		
			while (!tempDc.empty())
			{
				for (int i = 0; i < tempDc.size(); i++)
				{
					Dc.push_back(tempDc[i]);
				}
				tempDc.clear();

				for (int i = 0; i < Dc.size(); i++)
				{
					if (!Dc[i].bmb_near)
					{
						tempDc2 = arCell(Dc[i].i, Dc[i].j, V);

					}

					if (tempDc2.size())
					{
						for (int k = 0; k < tempDc2.size(); k++)
						{
							tempDc.push_back(tempDc2[k]);
						}

						tempDc2.clear();
					}
				}
			}
			Dc.clear();
		}
	return;

	}

	void SEARCH_AROUND(short i, short j, std::vector<std::vector<cell_values>>& V) {
		//cout << "==========SEARCH_AROUND_WAS_STARTED==========" << endl;

		if (i < 1 || i > V.size() - 2 || j < 1 || j > V[0].size() - 2) //���� ���� ����
		{
			return;
		}

		if (V[i][j].open) //���� ������ ��� �������
		{
			return;
		}

		if (V[i][j].bmb_near != 0) //���� ������ �� ����� ���� �� ��������� ����� � ���(����)
		{
			V[i][j].open = true;
			return;
		}

		if (!V[i][j].open && !V[i][j].bomb) //���� ��� �� ����� � ������ ������� ��������� �� � ���� � ���������
		{
			V[i][j].open = true;

			//��������
			SEARCH_AROUND(i - 1, j, V);
			SEARCH_AROUND(i + 1, j, V);
			SEARCH_AROUND(i, j - 1, V);
			SEARCH_AROUND(i, j + 1, V);

			if (!V[i][j].bmb_near)
			{
				if (!V[i + 1][j + 1].open )
				{
					SEARCH_AROUND(i + 1, j+1, V);
					V[i + 1] [j + 1] .open = true;
				}
				if (!V[i - 1][j + 1].open )
				{
					SEARCH_AROUND(i - 1, j + 1, V);
					V[i - 1][j + 1].open = true;
				}
				if (!V[i - 1][j - 1].open )
				{
					SEARCH_AROUND(i - 1, j - 1, V);
					V[i - 1][j - 1].open = true;
				}
				if (!V[i + 1][j - 1].open )
				{
					SEARCH_AROUND(i + 1, j - 1, V);
					V[i + 1][j - 1].open = true;
				}

			}
		
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

	////�����
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

	///notUsed
	//���������� ���-�� ������ ������ ������ i j ���� ��� �� �����
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

								this->SEARCH_AROUND2(mas[k].i, mas[k].j, V);
								//this->BLIT_AFTER_SEARCH(V);
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

	////��������� ����� � ������ i j � ��������� ���������� �������� ���(�������� ������ ������)
	void RIGHT_CLICK(std::vector<std::vector<cell_values>>&V, int i, int j) {
		if (!V[i][j].open) //�������� ��������� ������ 
		{
			std::cout << "JJJJJ\n";

			if (!V[i][j].flag && !V[i][j].question) // ����� ���
			{
				V[i][j].flag = true;
				this->flaCount++;
				if (V[i][j].bomb)
				{
					this->underFlagBombCount++;
				}
				return;
			}

			else if (V[i][j].flag)		// ���� ���� 
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

	//// �������� ����� ������ ����
	bool LEFT_CLICK(std::vector<std::vector<cell_values>>&V, int i, int j) {

		//������������� �������
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
				if (V[i][j].bmb_near>0)
				{
					if (!ROUND_OPEN_ROUND_SEARCH_FLAG(i, j, V))
					{
						//V[i][j].open = true;
						std::cout << "you lose " << std::endl;
						return false;
					}
					else return true;
				}
				else return true;
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
						 //this->SEARCH_AROUND(i, j, V);
						this->SEARCH_AROUND2(i, j, V);
						//this->BLIT_AFTER_SEARCH(V);
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

