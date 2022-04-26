#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>

//using namespace std;


enum TCell : char {
	CROSS = 'X',
	ZERO = '0',
	EMPTY = '_'
};

enum TGameStatus {
	IN_PROGRESS,
	PLAYER_WON,
	AI_WON,
	DRAW
};

#pragma pack(push, 1)
struct TGame {
	TCell** ppField = nullptr;
	size_t fsize{ 3 };
	TCell player{ CROSS };
	TCell AI{ ZERO };
	TGameStatus status{ IN_PROGRESS };
	size_t turn{ 0U };
};
#pragma pack(pop)

struct TCoord {
	size_t y{ 0 };
	size_t x{ 0 };
};

void __inline clrScr()
{
	system("cls");
	//std::cout << "\x1B[2J\x1B[H";
}

int32_t __fastcall getRandomNum(const int32_t min, const int32_t max)
{
	const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937_64 generator(seed);
	std::uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
	//return (min + (rand() % (max + min)));
}

void __fastcall startMenu(TGame& game)
{
	std::cout << "Hello, stranger!" << std::endl << "This is crosses and zeroes game." << std::endl <<
		"Enter the field size:" << std::endl;
	std::cin >> game.fsize;
}

void __fastcall initGame(TGame & game)
{
	game.ppField = new TCell * [game.fsize];
	for (int i = 0; i < game.fsize; i++)
	{
		game.ppField[i] = new TCell[game.fsize];
	}

	for (size_t y = 0; y < game.fsize; y++)
	{
		for (size_t x = 0; x < game.fsize; x++)
		{
			game.ppField[y][x] = EMPTY;
		}
	}

	if (getRandomNum(1, 1000) > 500)
	{
		game.player = CROSS;
		game.AI = ZERO;
		game.turn = 0U;
	}
	else
	{
		game.player = ZERO;
		game.AI = CROSS;
		game.turn = 1U;
	}
}

void __fastcall printGame(const TGame& game)
{
	//разметка:
	/*= | 1 | 2 | 3 | x
	  1 | _ | _ | _ |	    Player - X
	  2 | _ | _ | _ |	        AI - O
	  3 | _ | _ | _ |
	  y

	  Your turn!
	  Enter x: _
	  Enter y: _	*/
	if (game.fsize == 3)
	{
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "      " << "  | 1 | 2 | 3 | x" << std::endl;
		std::cout << "      " << "1 | " << game.ppField[0][0] << " | " << game.ppField[0][1] << " | " << game.ppField[0][2] << " | x" << "        Player:" << game.player << std::endl;
		std::cout << "      " << "2 | " << game.ppField[1][0] << " | " << game.ppField[1][1] << " | " << game.ppField[1][2] << " | x" << "            AI:" << game.AI << std::endl;
		std::cout << "      " << "3 | " << game.ppField[2][0] << " | " << game.ppField[2][1] << " | " << game.ppField[2][2] << " | x" << std::endl;
		std::cout << "      " << "y" << std::endl << std::endl;
	}
	else if(game.fsize == 4)
	{
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "      " << "  | 1 | 2 | 3 | 4 | x" << std::endl;
		std::cout << "      " << "1 | " << game.ppField[0][0] << " | " << game.ppField[0][1] << " | " << game.ppField[0][2] << " | " << game.ppField[0][3] << " | x" << "        Player:" << game.player << std::endl;
		std::cout << "      " << "2 | " << game.ppField[1][0] << " | " << game.ppField[1][1] << " | " << game.ppField[1][2] << " | " << game.ppField[1][3] << " | x" << "            AI:" << game.AI << std::endl;
		std::cout << "      " << "3 | " << game.ppField[2][0] << " | " << game.ppField[2][1] << " | " << game.ppField[2][2] << " | " << game.ppField[2][3] << " | x" << std::endl;
		std::cout << "      " << "4 | " << game.ppField[3][0] << " | " << game.ppField[3][1] << " | " << game.ppField[3][2] << " | " << game.ppField[3][3] << " | x" << std::endl;
		std::cout << "      " << "y" << std::endl << std::endl;
	}
	else if(game.fsize == 5)
	{
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "      " << "  | 1 | 2 | 3 | 4 | 5 | x" << std::endl;
		std::cout << "      " << "1 | " << game.ppField[0][0] << " | " << game.ppField[0][1] << " | " << game.ppField[0][2] << " | " << game.ppField[0][3] << " | " << game.ppField[0][4] << " | x" << "        Player:" << game.player << std::endl;
		std::cout << "      " << "2 | " << game.ppField[1][0] << " | " << game.ppField[1][1] << " | " << game.ppField[1][2] << " | " << game.ppField[1][3] << " | " << game.ppField[1][4] << " | x" << "            AI:" << game.AI << std::endl;
		std::cout << "      " << "3 | " << game.ppField[2][0] << " | " << game.ppField[2][1] << " | " << game.ppField[2][2] << " | " << game.ppField[2][3] << " | " << game.ppField[2][4] << " | x" << std::endl;
		std::cout << "      " << "4 | " << game.ppField[3][0] << " | " << game.ppField[3][1] << " | " << game.ppField[3][2] << " | " << game.ppField[3][3] << " | " << game.ppField[3][4] << " | x" << std::endl;
		std::cout << "      " << "5 | " << game.ppField[4][0] << " | " << game.ppField[4][1] << " | " << game.ppField[4][2] << " | " << game.ppField[4][3] << " | " << game.ppField[4][4] << " | x" << std::endl;
		std::cout << "      " << "y" << std::endl << std::endl;
	}


	std::cout << std::endl << std::endl;

}

void __fastcall deinitGame(TGame & game)
{
	for(int i = 0; i > game.fsize; i++)
	{
		delete[] game.ppField[i];
	}

	delete[] game.ppField;
}

TGameStatus __fastcall getWon(TGame & game)
{
	game.status = IN_PROGRESS;
	if (game.fsize == 3) //=========== 3*3 ================================
	{
		// проверить строки

		for (int y = 0; y < game.fsize; y++)
		{
			if (game.ppField[y][0] != EMPTY)
			{
				if (game.ppField[y][0] == game.ppField[y][1] && game.ppField[y][0] == game.ppField[y][2])
				{
					if (game.ppField[y][0] == game.player)
					{
						game.status = PLAYER_WON;
						return game.status;
					}
					else if (game.ppField[y][0] == game.AI)
					{
						game.status = AI_WON;
						return game.status;
					}
				}
			}
		}


		//проверить столбцы

		for (int x = 0; x < game.fsize; x++)
		{
			if (game.ppField[0][x] != EMPTY)
			{
				if (game.ppField[0][x] == game.ppField[1][x] && game.ppField[0][x] == game.ppField[2][x])
				{
					if (game.ppField[0][x] == game.player)
					{
						game.status = PLAYER_WON;
						return game.status;
					}
					else if (game.ppField[0][x] == game.AI)
					{
						game.status = AI_WON;
						return game.status;
					}
				}
			}
		}
		//проверить диагонали
		if (game.ppField[0][0] != EMPTY)
		{
			if (game.ppField[0][0] == game.ppField[1][1] && game.ppField[0][0] == game.ppField[2][2])
			{
				if (game.ppField[0][0] == game.player)
				{
					game.status = PLAYER_WON;
					return game.status;
				}
				else if (game.ppField[0][0] == game.AI)
				{
					game.status = AI_WON;
					return game.status;
				}
			}
		}

		if (game.ppField[0][2] != EMPTY)
		{
			if (game.ppField[0][2] == game.ppField[1][1] && game.ppField[0][2] == game.ppField[2][0])
			{
				if (game.ppField[0][2] == game.player)
				{
					game.status = PLAYER_WON;
					return game.status;
				}
				else if (game.ppField[0][2] == game.AI)
				{
					game.status = AI_WON;
					return game.status;
				}
			}
		}

		// проверка на ничью
		int counter = 0;
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					counter++;
				}


			}
		}
		if (counter == 0)
		{
			game.status = DRAW;
			return game.status;
		}


	}
	if (game.fsize == 4) //=========== 4*4 ================================
	{
		// проверить строки

		for (int y = 0; y < game.fsize; y++)
		{
			if (game.ppField[y][0] != EMPTY)
			{
				if (game.ppField[y][0] == game.ppField[y][1] && game.ppField[y][0] == game.ppField[y][2] && game.ppField[y][0] == game.ppField[y][3])
				{
					if (game.ppField[y][0] == game.player)
					{
						game.status = PLAYER_WON;
						return game.status;
					}
					else if (game.ppField[y][0] == game.AI)
					{
						game.status = AI_WON;
						return game.status;
					}
				}
			}
		}


		//проверить столбцы

		for (int x = 0; x < game.fsize; x++)
		{
			if (game.ppField[0][x] != EMPTY)
			{
				if (game.ppField[0][x] == game.ppField[1][x] && game.ppField[0][x] == game.ppField[2][x] && game.ppField[0][x] == game.ppField[3][x])
				{
					if (game.ppField[0][x] == game.player)
					{
						game.status = PLAYER_WON;
						return game.status;
					}
					else if (game.ppField[0][x] == game.AI)
					{
						game.status = AI_WON;
						return game.status;
					}
				}
			}
		}
		//проверить диагонали
		if (game.ppField[0][0] != EMPTY)
		{
			if (game.ppField[0][0] == game.ppField[1][1] && game.ppField[0][0] == game.ppField[2][2] && game.ppField[0][0] == game.ppField[3][3])
			{
				if (game.ppField[0][0] == game.player)
				{
					game.status = PLAYER_WON;
					return game.status;
				}
				else if (game.ppField[0][0] == game.AI)
				{
					game.status = AI_WON;
					return game.status;
				}
			}
		}

		if (game.ppField[0][3] != EMPTY)
		{
			if (game.ppField[0][3] == game.ppField[1][2] && game.ppField[0][3] == game.ppField[2][1] && game.ppField[0][3] == game.ppField[3][0])
			{
				if (game.ppField[0][3] == game.player)
				{
					game.status = PLAYER_WON;
					return game.status;
				}
				else if (game.ppField[0][3] == game.AI)
				{
					game.status = AI_WON;
					return game.status;
				}
			}
		}

		// проверка на ничью
		int counter = 0;
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					counter++;
				}


			}
		}
		if (counter == 0)
		{
			game.status = DRAW;
			return game.status;
		}


	}
	if (game.fsize == 4) //=========== 5*5 ================================
	{
		// проверить строки

		for (int y = 0; y < game.fsize; y++)
		{
			if (game.ppField[y][0] != EMPTY)
			{
				if (game.ppField[y][0] == game.ppField[y][1] && game.ppField[y][0] == game.ppField[y][2] && game.ppField[y][0] == game.ppField[y][3] && game.ppField[y][0] == game.ppField[y][4])
				{
					if (game.ppField[y][0] == game.player)
					{
						game.status = PLAYER_WON;
						return game.status;
					}
					else if (game.ppField[y][0] == game.AI)
					{
						game.status = AI_WON;
						return game.status;
					}
				}
			}
		}


		//проверить столбцы

		for (int x = 0; x < game.fsize; x++)
		{
			if (game.ppField[0][x] != EMPTY)
			{
				if (game.ppField[0][x] == game.ppField[1][x] && game.ppField[0][x] == game.ppField[2][x] && game.ppField[0][x] == game.ppField[3][x] && game.ppField[0][x] == game.ppField[4][x])
				{
					if (game.ppField[0][x] == game.player)
					{
						game.status = PLAYER_WON;
						return game.status;
					}
					else if (game.ppField[0][x] == game.AI)
					{
						game.status = AI_WON;
						return game.status;
					}
				}
			}
		}
		//проверить диагонали
		if (game.ppField[0][0] != EMPTY)
		{
			if (game.ppField[0][0] == game.ppField[1][1] && game.ppField[0][0] == game.ppField[2][2] && game.ppField[0][0] == game.ppField[3][3] && game.ppField[0][0] == game.ppField[3][3])
			{
				if (game.ppField[0][0] == game.player)
				{
					game.status = PLAYER_WON;
					return game.status;
				}
				else if (game.ppField[0][0] == game.AI)
				{
					game.status = AI_WON;
					return game.status;
				}
			}
		}

		if (game.ppField[0][4] != EMPTY)
		{
			if (game.ppField[0][4] == game.ppField[1][3] && game.ppField[0][4] == game.ppField[2][2] && game.ppField[0][4] == game.ppField[3][1] && game.ppField[0][4] == game.ppField[4][0])
			{
				if (game.ppField[0][4] == game.player)
				{
					game.status = PLAYER_WON;
					return game.status;
				}
				else if (game.ppField[0][4] == game.AI)
				{
					game.status = AI_WON;
					return game.status;
				}
			}
		}

		// проверка на ничью
		int counter = 0;
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					counter++;
				}


			}
		}
		if (counter == 0)
		{
			game.status = DRAW;
			return game.status;
		}


	}

	return game.status;

}

TCoord __fastcall getPlayerCoord(TGame& game)
{
	TCoord crd;
	do
	{
		std::cout << "      " << "Your turn!" << std::endl << "      " << " Enter x(1 - " << game.fsize << "):";
		std::cin >> crd.x;
		std::cout << std::endl << "      " << "Enter y(1 - " << game.fsize << "):";
		std::cin >> crd.y;
		crd.x--;
		crd.y--;

	} while ((crd.x > (game.fsize-1)) || (crd.y > (game.fsize - 1)) || (game.ppField[crd.y][crd.x] != EMPTY));


	return crd;
}

TCoord __fastcall getAICoord(TGame& game)
{
	TCoord coords;

	if (game.fsize == 3) //=============== 3*3 ===========================
	{
		// проверка на победу игрока
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					game.ppField[y][x] = game.player;
					getWon(game);
					if (game.status == PLAYER_WON)
					{
						game.ppField[y][x] = EMPTY;
						coords.x = x;
						coords.y = y;
						return coords;
					}
					else
					{
						game.ppField[y][x] = EMPTY;
					}
				}


			}
		}

		// проверка на победу ПК
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					game.ppField[y][x] = game.AI;
					getWon(game);
					if (game.status == AI_WON)
					{
						game.ppField[y][x] = EMPTY;
						coords.x = x;
						coords.y = y;
						return coords;
					}
					else
					{
						game.ppField[y][x] = EMPTY;
					}
				}
			}
		}

		// приоритетная установка
		if (game.ppField[1][1] == EMPTY)
		{
			coords.x = 1;
			coords.y = 1;
			return coords;
		}

		int count = 0;
		TCoord crdAr[4];
		if (game.ppField[0][0] == EMPTY)
		{
			crdAr[count]={ 0 , 0 };
			count++;
		}
		if (game.ppField[0][2] == EMPTY)
		{
			crdAr[count]={ 0 , 2 };
			count++;
		}
		if (game.ppField[2][0] == EMPTY)
		{
			crdAr[count]={ 2 , 0 };
			count++;
		}
		if (game.ppField[2][2] == EMPTY)
		{
			crdAr[count]={ 2 , 2 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}


		if (game.ppField[0][1] == EMPTY)
		{
			crdAr[count]={ 0 , 1 };
			count++;
		}
		if (game.ppField[1][0] == EMPTY)
		{
			crdAr[count]={ 1 , 0 };
			count++;
		}
		if (game.ppField[1][2] == EMPTY)
		{
			crdAr[count]={ 1 , 2 };
			count++;
		}
		if (game.ppField[2][1] == EMPTY)
		{
			crdAr[count]={ 2 , 1 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}
	}
	if (game.fsize == 4) //=============== 4*4 ===========================
	{
		// проверка на победу игрока
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					game.ppField[y][x] = game.player;
					getWon(game);
					if (game.status == PLAYER_WON)
					{
						game.ppField[y][x] = EMPTY;
						coords.x = x;
						coords.y = y;
						return coords;
					}
					else
					{
						game.ppField[y][x] = EMPTY;
					}
				}


			}
		}

		// проверка на победу ПК
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					game.ppField[y][x] = game.AI;
					getWon(game);
					if (game.status == AI_WON)
					{
						game.ppField[y][x] = EMPTY;
						coords.x = x;
						coords.y = y;
						return coords;
					}
					else
					{
						game.ppField[y][x] = EMPTY;
					}
				}
			}
		}

		// приоритетная установка

		int count = 0;
		TCoord crdAr[8];

		//central square
		if (game.ppField[1][1] == EMPTY)
		{
			crdAr[count] = { 1 , 1 };
			count++;
		}
		if (game.ppField[1][2] == EMPTY)
		{
			crdAr[count] = { 1 , 2 };
			count++;
		}
		if (game.ppField[2][1] == EMPTY)
		{
			crdAr[count] = { 2 , 1 };
			count++;
		}
		if (game.ppField[2][2] == EMPTY)
		{
			crdAr[count] = { 2 , 2 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}

		//corners
		if (game.ppField[0][0] == EMPTY)
		{
			crdAr[count] = { 0 , 0 };
			count++;
		}
		if (game.ppField[0][3] == EMPTY)
		{
			crdAr[count] = { 0 , 3 };
			count++;
		}
		if (game.ppField[3][0] == EMPTY)
		{
			crdAr[count] = { 3 , 0 };
			count++;
		}
		if (game.ppField[3][3] == EMPTY)
		{
			crdAr[count] = { 3 , 3 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}

		// sides
		if (game.ppField[0][1] == EMPTY)
		{
			crdAr[count] = { 0 , 1 };
			count++;
		}
		if (game.ppField[1][0] == EMPTY)
		{
			crdAr[count] = { 1 , 0 };
			count++;
		}
		if (game.ppField[0][2] == EMPTY)
		{
			crdAr[count] = { 0 , 2 };
			count++;
		}
		if (game.ppField[2][0] == EMPTY)
		{
			crdAr[count] = { 2 , 0 };
			count++;
		}
		if (game.ppField[3][1] == EMPTY)
		{
			crdAr[count] = { 3 , 1 };
			count++;
		}
		if (game.ppField[1][3] == EMPTY)
		{
			crdAr[count] = { 1 , 3 };
			count++;
		}
		if (game.ppField[3][2] == EMPTY)
		{
			crdAr[count] = { 3 , 2 };
			count++;
		}
		if (game.ppField[2][3] == EMPTY)
		{
			crdAr[count] = { 2 , 3 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}
	}

	if (game.fsize == 5) //=============== 5*5 ===========================
	{
		// проверка на победу игрока
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					game.ppField[y][x] = game.player;
					getWon(game);
					if (game.status == PLAYER_WON)
					{
						game.ppField[y][x] = EMPTY;
						coords.x = x;
						coords.y = y;
						return coords;
					}
					else
					{
						game.ppField[y][x] = EMPTY;
					}
				}


			}
		}

		// проверка на победу ПК
		for (int y = 0; y < game.fsize; y++)
		{
			for (int x = 0; x < game.fsize; x++)
			{
				if (game.ppField[y][x] == EMPTY)
				{
					game.ppField[y][x] = game.AI;
					getWon(game);
					if (game.status == AI_WON)
					{
						game.ppField[y][x] = EMPTY;
						coords.x = x;
						coords.y = y;
						return coords;
					}
					else
					{
						game.ppField[y][x] = EMPTY;
					}
				}
			}
		}

		// приоритетная установка


		//central cell
		if (game.ppField[2][2] == EMPTY)
		{
			coords.x = 2;
			coords.y = 2;
			return coords;
		}

		int count = 0;
		TCoord crdAr[8];

		//inner circle corners
		if (game.ppField[1][1] == EMPTY)
		{
			crdAr[count] = { 1 , 1 };
			count++;
		}
		if (game.ppField[1][3] == EMPTY)
		{
			crdAr[count] = { 1 , 3 };
			count++;
		}
		if (game.ppField[3][1] == EMPTY)
		{
			crdAr[count] = { 3 , 1 };
			count++;
		}
		if (game.ppField[3][3] == EMPTY)
		{
			crdAr[count] = { 3 , 3 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}

		//inner circle sides
		if (game.ppField[2][1] == EMPTY)
		{
			crdAr[count] = { 2 , 1 };
			count++;
		}
		if (game.ppField[1][2] == EMPTY)
		{
			crdAr[count] = { 1 , 2 };
			count++;
		}
		if (game.ppField[3][2] == EMPTY)
		{
			crdAr[count] = { 3 , 2 };
			count++;
		}
		if (game.ppField[2][3] == EMPTY)
		{
			crdAr[count] = { 2 , 3 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}

		//outer circle corners
		if (game.ppField[0][0] == EMPTY)
		{
			crdAr[count] = { 0 , 0 };
			count++;
		}
		if (game.ppField[0][4] == EMPTY)
		{
			crdAr[count] = { 0 , 4 };
			count++;
		}
		if (game.ppField[4][0] == EMPTY)
		{
			crdAr[count] = { 4 , 0 };
			count++;
		}
		if (game.ppField[4][4] == EMPTY)
		{
			crdAr[count] = { 4 , 4 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}

		//outer circle side centrals
		if (game.ppField[0][2] == EMPTY)
		{
			crdAr[count] = { 0 , 2 };
			count++;
		}
		if (game.ppField[2][4] == EMPTY)
		{
			crdAr[count] = { 2 , 4 };
			count++;
		}
		if (game.ppField[4][2] == EMPTY)
		{
			crdAr[count] = { 4 , 2 };
			count++;
		}
		if (game.ppField[2][0] == EMPTY)
		{
			crdAr[count] = { 2 , 0 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}

		//outer circle semi sides
		if (game.ppField[0][1] == EMPTY)
		{
			crdAr[count] = { 0 , 1 };
			count++;
		}
		if (game.ppField[1][0] == EMPTY)
		{
			crdAr[count] = { 1 , 0 };
			count++;
		}
		if (game.ppField[4][1] == EMPTY)
		{
			crdAr[count] = { 4 , 1 };
			count++;
		}
		if (game.ppField[1][4] == EMPTY)
		{
			crdAr[count] = { 1 , 4 };
			count++;
		}
		if (game.ppField[3][0] == EMPTY)
		{
			crdAr[count] = { 3 , 0 };
			count++;
		}
		if (game.ppField[0][3] == EMPTY)
		{
			crdAr[count] = { 0 , 3 };
			count++;
		}
		if (game.ppField[3][4] == EMPTY)
		{
			crdAr[count] = { 3 , 4 };
			count++;
		}
		if (game.ppField[4][3] == EMPTY)
		{
			crdAr[count] = { 4 , 3 };
			count++;
		}
		if (count > 0)
		{
			count--;
			coords = crdAr[getRandomNum(0, count)];
			return coords;
		}
	}
}

char grats(const TGame& game)
{
	if (game.status == PLAYER_WON)
	{
		std::cout << "Yeeehaw! You win!";
	}
	else if (game.status == AI_WON)
	{
		std::cout << "Ha-ha! You lose!";
	}
	else if (game.status == DRAW)
	{
		std::cout << "Draw game. Boring.";
	}

	std::cout << std::endl << "Enter 'q' for quit, 'r' for replay:";

		char rorq;
	do {
		std::cin >> rorq;
	} while (rorq != 'q' && rorq != 'r');

	return rorq;

}

int main()
{
	label1:
	TGame game;

	startMenu(game);

	initGame(game);


	do
	{
		clrScr();
		printGame(game);
		if ((game.turn % 2) == 0)
		{
			TCoord crd = getPlayerCoord(game);
			game.ppField[crd.y][crd.x] = game.player;
		}
		else
		{
			TCoord crd = getAICoord(game);
			game.ppField[crd.y][crd.x] = game.AI;
		}
		game.turn++;
		getWon(game);
	} while (game.status == IN_PROGRESS);

	clrScr();
	printGame(game);

	deinitGame(game);

	if (grats(game) == 'q')
	{
		std::cout << std::endl << "Press enter to quit";
		getchar(); getchar();
	}
	else
	{
		goto label1;
	}

	return 0;
}
