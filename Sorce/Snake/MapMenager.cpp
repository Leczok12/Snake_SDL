#include "MapMenager.h"


MapMenager::MapMenager( int yxYXpos , int sSide, int oOldSide, int lLength)
{
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			YXposNUM[y][x] = yxYXpos;
		};
	};

	side = sSide;
	oldSide = oOldSide;
	length = lLength; 
	globalError = false;
	reset();
};

MapMenager::~MapMenager()
{

};
void MapMenager::newApple(AudioMenager* AU)
{
	bool isApple = false;
	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x < 11; x++)
		{
			if (YXposNUM[y][x] == APPLE)
			{
				isApple = true;
			}
		}
	}

	if (isApple == false)
	{
		bool seek = true;
		do {
			for (int y = 1; y < 11; y++)
			{
				for (int x = 1; x < 11; x++)
				{
					int setApple = SDL_GetTicks() % 10;
					if ((YXposNUM[y][x] == 0) && (setApple == 3) && (seek == true))
					{
						YXposNUM[y][x] = APPLE;
						AU->play();
						length++;
						seek = false;
					}
				}
			};

		} while (seek == true);
	}
};

void MapMenager::updatePos(AudioMenager* AU)
{
	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x < 11; x++)
		{
			if (YXposNUM[y][x] == 1)
			{
				switch (side)
				{
				case 1:
					if (YXposNUM[y - 1][x] == NOT_ALLOWED_SPACE)
					{
						snakeControl(true);
					};
					break;

				case 2:
					if (YXposNUM[y][x - 1] == NOT_ALLOWED_SPACE)
					{
						snakeControl(true);
					};
					break;

				case 3:
					if (YXposNUM[y][x + 1] == NOT_ALLOWED_SPACE)
					{
						snakeControl(true);
					};
					break;

				case 4:
					if (YXposNUM[y + 1][x] == NOT_ALLOWED_SPACE)
					{
						snakeControl(true);
					};
					break;
				};
				
			};
		};
	};

	newApple(AU);
	bool BREAK = false;
	for (int i = length; i >= 1; i--)
	{
		for (int y = 1; y < 11; y++)
		{
			for (int x = 1; x < 11; x++)
			{
				if (BREAK == false)
				{
					if ((i >= 1) && (YXposNUM[y][x] == i) && (i < length))
					{
						YXposNUM[y][x] = i + 1;
						BREAK = true;
					}
					else if ((YXposNUM[y][x] == length) && (i == length))
					{
						YXposNUM[y][x] = 0;
						BREAK = true;
					};
				};
			};
		};
		BREAK = false;
	};

	BREAK = false;

	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x < 11; x++)
		{
			if (BREAK == false)
			{
				if (YXposNUM[y][x] == 2)
				{
					switch (side)
					{
					case 1:
						if ((YXposNUM[y - 1][x] == EMPTY_SPACE) || (YXposNUM[y - 1][x] == APPLE))
						{
							YXposNUM[y - 1][x] = 1;
							oldSide = 1;
						}
						else
						{
							snakeControl(true);
						};
						break;

					case 2:
						if ((YXposNUM[y][x - 1] == EMPTY_SPACE) || (YXposNUM[y][x - 1] == APPLE))
						{
							YXposNUM[y][x - 1] = 1;
							oldSide = 2;
						}
						else
						{
							snakeControl(true);
						};
						break;

					case 3:
						if ((YXposNUM[y][x + 1] == EMPTY_SPACE) || (YXposNUM[y][x + 1] == APPLE))
						{
							YXposNUM[y][x + 1] = 1;
							oldSide = 3;
						}
						else
						{
							snakeControl(true);
						};
						break;

					case 4:
						if ((YXposNUM[y + 1][x] == EMPTY_SPACE) || (YXposNUM[y + 1][x] == APPLE))
						{
							YXposNUM[y + 1][x] = 1;
							oldSide = 4;
						}
						else
						{
							snakeControl(true);
						};
						break;
					};
					BREAK = true;
				};
			};
		};
	};
};


void MapMenager::snakeControl(bool error)
{
	if (error == true)
	{
		globalError = true;
	};
};



void MapMenager::reset()
{
	HM.reset();
	globalError = false;
	for (int y = 0; y < 12; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			if (y == 0 || x == 0 || y == 11 || x == 11)
			{
				YXposNUM[y][x] = NOT_ALLOWED_SPACE;
			}
			else
			{
				YXposNUM[y][x] = EMPTY_SPACE;
			};
		};
	};

	YXposNUM[5][3] = 1;
	YXposNUM[5][2] = 2;
	YXposNUM[5][1] = 3;

	YXposNUM[5][8] = APPLE;

	side = 3;
	oldSide = 3;
	length = 3;
};
void MapMenager::renderCrash(SDL_Renderer* R, SDL_Texture* T, AudioMenager* AU)
{
	
	if (globalError == true)// 1 - up, 2 - left, 3 - right, 4 - down 
	{
		int Rx, Ry;
		for (int y = 0; y < 12; y++)
		{
			for (int x = 0; x < 12; x++)
			{
				if (YXposNUM[y][x] == 2)
				{
					Rx = ((x - 1) * 70) + (-20);
					Ry = ((y - 1) * 70) + 80;
				}
			};
		};
		switch (side)
		{
		case 1:
			HM.Show(R, T, AU, -90, Rx, Ry);
			break;
		case 2:
			HM.Show(R, T, AU, 180, Rx, Ry);
			break;
		case 3:
			HM.Show(R, T, AU, 0, Rx, Ry);
			break;
		case 4:
			HM.Show(R, T, AU, 90, Rx, Ry);
			break;
		};
	};
};

void MapMenager::sideChange(int s, AudioMenager* AU, bool pause) // 1 - up, 2 - left, 3 - right, 4 - down 
{
	if ((pause != true)&&(globalError == false))
	{
		if ((s == 1) && (oldSide != 4) && (side != 1))
		{
			side = 1;
			AU->play();
		}
		else if ((s == 2) && (oldSide != 3) && (side != 2))
		{
			side = 2;
			AU->play();
		}
		else if ((s == 3) && (oldSide != 2) && (side != 3))
		{
			side = 3;
			AU->play();
		}
		else if ((s == 4) && (oldSide != 1) && (side != 4))
		{
			side = 4;
			AU->play();
		};
	};
};

bool MapMenager::checkError()
{
	return globalError;
}