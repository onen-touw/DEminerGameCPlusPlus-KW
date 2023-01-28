#pragma once

#include"setting.h"
#include<string>
#include<fstream>

class saveGame
{

private:
	int gameCount = 0;

	uint32_t timeFromSave = 0;


	std::vector<std::vector<int>> statMatrix;
	std::string tempStr;
	std::string tempStr2;

	int hardnessF = 0;
	int hardnessB = 0;
	
	int tableLines = 9, tableColumns = 3;

public:
	~saveGame()
	{
		statMatrix.clear();
	}
	
	saveGame() {
		statMatrix.resize(this->tableLines);
		for (int i = 0; i < statMatrix.size(); i++)
		{
			statMatrix[i].resize(this->tableColumns);
		}
	}

	uint32_t getTime() { return timeFromSave; }

	//int getGameCount() { return gameCount; }

	void DataOpen(){
		//statMatrix.clear();
		gameCount = 0;

		std::ifstream file("save/data.txt");
		if (file.is_open()) {
			std::cout << "data is open\n"; 
			for (int i = 0; i < 10; i++)
			{
				
				if (i == 0)
				{
					std::getline(file, tempStr);
					gameCount = atoi(tempStr.c_str());
					std::cout << gameCount << "<< gCount\n";
					tempStr.clear();
				}
				else
				{
					std::getline(file, tempStr);
					int k = 0, j = 0;
					while (tempStr[k] != '\0')
					{
						if (tempStr[k] != '/')
						{
							tempStr2.append(1, tempStr[k]);
						}
						else
						{
							statMatrix[i - 1][j] = (atoi(tempStr2.c_str()));
							tempStr2.clear();
							j++;
						}
						k ++ ;
					}
				}	
			}
			std::cout << "\n";
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j <3; j++)
				{
					std::cout << statMatrix[i][j] << " ";

				}
				std::cout << "\n";
			}
			std::cout << "\n";


		}
		file.close();
	}

	std::vector<std::vector<int>>getStat() { return this->statMatrix; }
	int getGameCount() { return this->gameCount; }

	void DataSave(int hF, int hB, int winStatus, int time) {
		std::ofstream file("save/data.txt", std::ios::out);

		gameCount++;
		int block = 3 * hF;

		this->statMatrix[block + hB][0]++; ///+game
		if (winStatus)
		{
			this->statMatrix[block + hB][1]++; /// +win / +0
			if (time < this->statMatrix[block + hB][2] || statMatrix[block + hB][2] == 0)
			{
				this->statMatrix[block + hB][2] = time;

			}
		}
		
		if (file.is_open())
		{
			std::cout << "open4Update\n";
			file << gameCount << "\n";
			for (int i = 0; i < this->statMatrix.size(); i++)
			{
				for (int j	= 0; j < this->statMatrix[0].size(); j++)
				{
					file << this->statMatrix[i][j] << "/";
				}
				file << "\n";
			}
		}
		file.close();
	}

	bool LastGameOpen(std::vector<std::vector<cell_values>>& Field, short& fC, short&ufC, Uint32& time){
		std::ifstream file("save/lastG.txt");
		if (file.is_open())
		{
			std::getline(file, tempStr);
			if (tempStr[0] != '\0')
			{
				int hardnessF = atoi(tempStr.c_str());
				gameSetting::difficultG.updateFieldSize(hardnessF);
				gameSetting::hardnessField = hardnessF;

				std::getline(file, tempStr);
				int hardnessB = atoi(tempStr.c_str());
				gameSetting::difficultG.updateBombDensity(hardnessB);
				gameSetting::hardnessBomb = hardnessB;


				std::getline(file, tempStr);
				time = atoi(tempStr.c_str());

				std::getline(file, tempStr);
				fC = atoi(tempStr.c_str());

				std::getline(file, tempStr);
				ufC = atoi(tempStr.c_str());
				
				Field.clear();

				Field.resize(gameSetting::difficultG.gH);
				for (int i = 0; i < gameSetting::difficultG.gH; i++)
				{
					Field[i].resize(gameSetting::difficultG.gW);
				}


				int l = 0, m = 0, k = 0;
				while (std::getline(file, tempStr))
				{
					k = 0;
					m = 0;
					while (tempStr[k] != '\0')
					{
						if (tempStr[k] == '/')
						{
							k++;
						}
						if (tempStr[k] == '\0')
						{
							break;
						}

						Field[l][m].bomb = bool(tempStr[k] - '0');
						Field[l][m].open = bool(tempStr[++k] - '0');
						Field[l][m].flag = bool(tempStr[++k] - '0');
						Field[l][m].bmb_near = tempStr[++k] - '0';
						Field[l][m].question = bool(tempStr[++k] - '0');
						m++;
						k++;
					}
					l++;

				}

			}
			else
			{
				std::cout << "fuckU\n";
				return false;
			}
		}
		file.close();

		std::ofstream f("save/lastG.txt", std::ios::out); 
		f.close();

		return true;
	}

	void LastGameSave(std::vector<std::vector<cell_values>> &Field, 
		int hardnessF, int hardnessB, int time, int flagCount, int underflagCount)
	{
		std::ofstream file("save/lastG.txt", std::ios::out);
		if (file.is_open())
		{
			file << hardnessF << "\n";
			file << hardnessB << "\n";
			file << time << "\n";
			file << flagCount << "\n";
			file << underflagCount << "\n";

			for (int i = 0; i < Field.size(); i++)
			{
				for (int j = 0; j < Field[0].size(); j++)
				{
					file << Field[i][j].bomb 
						<< Field[i][j].open 
						<< Field[i][j].flag   
						<< Field[i][j].bmb_near 
						<< Field[i][j].question 
						<< "/";
				}
				file << "\n";
			}

		}

		file.close();
	}

	void lastSaveDel() {
		std::ofstream f("save/lastG.txt", std::ios::out);
		f.close();
	}

	//std::vector< std::vector <int>> getStatMatrix() { return statMatrix; }
	
};

