#include "SnakeRender.h"


SnakeRender::SnakeRender(Uint32 sSpeed,int add)
{
	//Set snake variables

	oldTimeSnake = 0;
	oldTimeskeletonMode = 0;
	speed = sSpeed;
	interspaceAdd = 0;
	plusInterspace = add;

	nStep = true;
	skeletonMode = false;

	snakeRect.x = -100;
	snakeRect.y = -100;
	snakeRect.w = 70;
	snakeRect.h = 70;
	
	snakePoint.x = 35;
	snakePoint.y = 35;

	param = 0;
	result = 0;

	appleX = 0;
	appleY = 0;

	isNear = false;
	moutchRect = { 0,0,0,0 };
	openSize = 0;
	oldTimeMountch = 0;
}

SnakeRender::~SnakeRender()
{
}

void SnakeRender::SetSpeed(int speedMode)
{
	switch (speedMode)
	{
	case 0:
		speed = 10;
		plusInterspace = 2;
		break;
	case 1:
		speed = 10;
		plusInterspace = 4;
		break;
	case 2:
		speed = 10;
		plusInterspace = 6;
		break;
	case 3:
		speed = 10;
		plusInterspace = 8;
		break;
	case 4:
		speed = 5;
		plusInterspace = 10;
		break;
	case 5:
		speed = 5;
		plusInterspace = 15;
		break;
	default:
		speed = 10;
		plusInterspace = 20;
		break;
	}
}
void SnakeRender::SetShowSkeleton()
{
	if (SDL_GetTicks() > (oldTimeskeletonMode + 200))
	{
		if (skeletonMode == false)
		{
			skeletonMode = true;
		}
		else
		{
			skeletonMode = false;
		};
		oldTimeskeletonMode = SDL_GetTicks();
	};
}

void SnakeRender::RSnake(SDL_Renderer* Render, SDL_Texture* headTexture, SDL_Texture* dotTexture, SDL_Texture* bodyTexture, SDL_Texture* eyesTexture, SDL_Texture* eyeTexture, SDL_Texture* moutchTexture, int YXNumArray[12][12], int lenght, bool isPause)
{
	if (skeletonMode == true)
	{
		for (int i = 1; i <= lenght; i++)
		{
			for (int y = 0; y < 12; y++)
			{
				for (int x = 0; x < 12; x++)
				{
					if (YXNumArray[y][x] == i)
					{
						SDL_Rect rect;
						rect.w = 70;
						rect.h = 70;
						rect.x = (x - 1) * 70 + 50;
						rect.y = (y - 1) * 70 + 150;
						SDL_SetRenderDrawColor(Render, 255, 0, 255, 255);
						SDL_RenderDrawRect(Render, &rect);
					};
				}
			}
		}
	}
	for (int i = 2; i < lenght; i++)
	{
		for (int y = 0; y < 12; y++)
		{
			for (int x = 0; x < 12; x++)
			{
				if (YXNumArray[y][x] == 420)
				{
					appleX = (x - 1) * 70 + 50;
					appleY = (y - 1) * 70 + 150;
				};
				if (YXNumArray[y][x] == i)
				{
					snakePoint.x = 35;
					snakePoint.y = 35;
					snakeRect.w = 70;
					snakeRect.h = 70;
					snakeRect.x = (x - 1) * 70 + 50;
					snakeRect.y = (y - 1) * 70 + 150;
					if ((YXNumArray[y][x - 1] == i - 1) && (YXNumArray[y][x + 1] == i + 1) && (i != 2))
					{
						snakeRect.x -= 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					}
					else if ((YXNumArray[y][x + 1] == i - 1) && (YXNumArray[y][x - 1] == i + 1) && (i != 2))
					{
						snakeRect.x += 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					}
					else if ((YXNumArray[y - 1][x] == i - 1) && (YXNumArray[y + 1][x] == i + 1) && (i != 2))
					{
						snakeRect.y -= 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);
					}
					else if ((YXNumArray[y + 1][x] == i - 1) && (YXNumArray[y - 1][x] == i + 1) && (i != 2))
					{
						snakeRect.y += 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);
					}
					else if ((((YXNumArray[y][x - 1] == i + 1) && (YXNumArray[y - 1][x] == i - 1)) || ((YXNumArray[y][x + 1] == i + 1) && (YXNumArray[y - 1][x] == i - 1))) && (i != 2)) //up
					{
						SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
						snakeRect.y -= 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);
					}
					else if ((((YXNumArray[y][x - 1] == i + 1) && (YXNumArray[y + 1][x] == i - 1)) || ((YXNumArray[y][x + 1] == i + 1) && (YXNumArray[y + 1][x] == i - 1))) && (i != 2)) //down
					{
						SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
						snakeRect.y += 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);
					}
					else if ((((YXNumArray[y + 1][x] == i + 1) && (YXNumArray[y][x + 1] == i - 1)) || ((YXNumArray[y - 1][x] == i + 1) && (YXNumArray[y][x + 1] == i - 1))) && (i != 2)) //right
					{
						SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
						snakeRect.x += 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					}
					else if ((((YXNumArray[y + 1][x] == i + 1) && (YXNumArray[y][x - 1] == i - 1)) || ((YXNumArray[y - 1][x] == i + 1) && (YXNumArray[y][x - 1] == i - 1))) && (i != 2)) //left
					{
						SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
						snakeRect.x -= 35;
						SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					}
					else
					{
						SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					};
				}
			}
		}
	}

	snakePoint.x = 35;
	snakePoint.y = 35;
	snakeRect.w = 70;
	snakeRect.h = 70;

	for (int y = 1; y < 11; y++) //tail
	{
		for (int x = 1; x < 11; x++)
		{
			if (YXNumArray[y][x] == lenght)
			{
				snakeRect.x = (x - 1) * 70 + 50;
				snakeRect.y = (y - 1) * 70 + 150;
				if (YXNumArray[y][x - 1] == lenght - 1)
				{
					snakeRect.x -= interspaceAdd;
					SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.x += interspaceAdd-35;
					snakeRect.w -= interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
				}
				else if (YXNumArray[y][x + 1] == lenght - 1)
				{
					snakeRect.x += interspaceAdd;
					SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.x += 35;
					snakeRect.w -= interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
				}
				else if (YXNumArray[y - 1][x] == lenght - 1)
				{
					snakeRect.y -= interspaceAdd;
					SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.y += interspaceAdd - 35;
					snakeRect.w -= interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);
				}
				else if (YXNumArray[y + 1][x] == lenght - 1)
				{
					snakeRect.y += interspaceAdd;
					SDL_RenderCopyEx(Render, dotTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.y += 35;
					snakeRect.w -= interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);
				};
			}
		}
	}

	snakePoint.x = 35;
	snakePoint.y = 35;
	snakeRect.w = 70;
	snakeRect.h = 70;

	bool isFinde = false;
	for (int y = 1; y < 11; y++) //head
	{
		for (int x = 1; x < 11; x++)
		{
			if (YXNumArray[y][x] == 1)
			{
				for (int yA = y-2; yA <= y+2; yA++)
				{
					for (int xA = x-2; xA <= x+2; xA++)
					{
						if (YXNumArray[yA][xA] == 420)
						{
							isNear = true;
							isFinde = true;
						}
						else if (isFinde == false)
						{
							isNear = false;
						};
					}
				}
				snakeRect.x = (x - 1) * 70 + 50;
				snakeRect.y = (y - 1) * 70 + 150;
				int clearY = snakeRect.y, clearX = snakeRect.x;
				if (YXNumArray[y][x - 1] == 2)
				{
					snakeRect.x -= 35;
					snakeRect.w = 0;
					snakeRect.w += interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);

					snakeRect.w = 70;
					snakeRect.x = clearX - 70 + interspaceAdd;
					SDL_RenderCopyEx(Render, headTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);
					SDL_RenderCopyEx(Render, eyesTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);


					long double lenghtX = appleX - (long double)snakeRect.x;
					long double lenghtY = appleY - (long double)clearY;

					result = atan2(lenghtY, lenghtX) * 180 / 3.14159265;

					snakePoint.x = 35;
					snakePoint.y = 35;
					snakeRect.w = 70;
					snakeRect.h = 70;
					snakeRect.x = clearX - 90 + interspaceAdd;
					snakeRect.y = clearY - 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.y = clearY + 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);
					
					if (isNear == true)
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) - openSize/2)-55+ interspaceAdd;
							moutchRect.y = ((y - 1) * 70 + 185) - openSize/2;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize < 70)
							{
								openSize += 10;
							};

							oldTimeMountch = SDL_GetTicks();
						};
						
						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, 0, &snakePoint, (SDL_RendererFlip)0);
					}
					else
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) - openSize / 2) - 55 + interspaceAdd;
							moutchRect.y = ((y - 1) * 70 + 185) - openSize / 2;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize > 0)
							{
								openSize -= 2;
							};
							if (openSize == 30)
							{
								openSize = 0;
							}
							oldTimeMountch = SDL_GetTicks();
						};
						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, 0, &snakePoint, (SDL_RendererFlip)0);
					};
				}
				else if (YXNumArray[y][x + 1] == 2)
				{
					snakeRect.x -= interspaceAdd - 105;
					snakeRect.w = 0;
					snakeRect.w += interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 0, &snakePoint, (SDL_RendererFlip)0);

					snakeRect.w = 70;
					snakeRect.x = clearX + 70 - interspaceAdd;
					SDL_RenderCopyEx(Render, headTexture, NULL, &snakeRect, 180, &snakePoint, (SDL_RendererFlip)0);
					SDL_RenderCopyEx(Render, eyesTexture, NULL, &snakeRect, 180, &snakePoint, (SDL_RendererFlip)0);

					long double lenghtX = appleX - (long double)snakeRect.x;
					long double lenghtY = appleY - (long double)clearY;

					result = atan2(lenghtY, lenghtX) * 180 / 3.14159265;

					snakePoint.x = 35;
					snakePoint.y = 35;
					snakeRect.w = 70;
					snakeRect.h = 70;
					snakeRect.x = clearX + 90 - interspaceAdd;
					snakeRect.y = clearY - 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.y = clearY + 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);

					if (isNear == true)
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) + openSize / 2) - interspaceAdd - 15;
							moutchRect.y = (((y - 1) * 70 + 185) + openSize / 2) -70;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize < 70)
							{
								openSize += 10;
							};

							oldTimeMountch = SDL_GetTicks();
						};

						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, 180, &snakePoint, (SDL_RendererFlip)0);
					}
					else
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) + openSize / 2) - interspaceAdd - 15;
							moutchRect.y = (((y - 1) * 70 + 185) + openSize / 2) - 70;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize > 0)
							{
								openSize -= 2;
							};
							if (openSize == 30)
							{
								openSize = 0;
							}
							oldTimeMountch = SDL_GetTicks();
						};
						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, 180, &snakePoint, (SDL_RendererFlip)0);
					};
				}
				else if (YXNumArray[y - 1][x] == 2)
				{
					snakeRect.y -= 35;
					snakeRect.w = 0;
					snakeRect.w += interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);

					snakeRect.w = 70;
					snakeRect.y = clearY - 70 + interspaceAdd;
					SDL_RenderCopyEx(Render, headTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);
					SDL_RenderCopyEx(Render, eyesTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);

					long double lenghtX = appleX - (long double)clearX;
					long double lenghtY = appleY - (long double)snakeRect.y;

					result = atan2(lenghtY, lenghtX) * 180 / 3.14159265;

					snakePoint.x = 35;
					snakePoint.y = 35;
					snakeRect.w = 70;
					snakeRect.h = 70;
					snakeRect.y = clearY - 90 + interspaceAdd;
					snakeRect.x = clearX - 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.x = clearX + 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);
					if (isNear == true)
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) + openSize / 2) - 70;
							moutchRect.y = (((y - 1) * 70 + 185) - openSize / 2) - 55 + interspaceAdd;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize < 70)
							{
								openSize += 10;
							};

							oldTimeMountch = SDL_GetTicks();
						};

						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, 90, &snakePoint, (SDL_RendererFlip)0);
					}
					else
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) + openSize / 2) - 70;
							moutchRect.y = (((y - 1) * 70 + 185) - openSize / 2) - 55 + interspaceAdd;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize > 0)
							{
								openSize -= 2;
							};
							if (openSize == 30)
							{
								openSize = 0;
							}
							oldTimeMountch = SDL_GetTicks();
						};
						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, 90, &snakePoint, (SDL_RendererFlip)0);
					};
				}
				else if (YXNumArray[y + 1][x] == 2)
				{
					snakeRect.y -= interspaceAdd - 105;
					snakeRect.w = 0;
					snakeRect.w += interspaceAdd;
					SDL_RenderCopyEx(Render, bodyTexture, NULL, &snakeRect, 90, &snakePoint, (SDL_RendererFlip)0);

					snakeRect.w = 70;
					snakeRect.y = clearY + 70 - interspaceAdd;
					SDL_RenderCopyEx(Render, headTexture, NULL, &snakeRect, -90, &snakePoint, (SDL_RendererFlip)0);
					SDL_RenderCopyEx(Render, eyesTexture, NULL, &snakeRect, -90, &snakePoint, (SDL_RendererFlip)0);

					long double lenghtX = appleX - (long double)clearX;
					long double lenghtY = appleY - (long double)snakeRect.y;

					result = atan2(lenghtY, lenghtX) * 180 / 3.14159265;

					snakePoint.x = 35;
					snakePoint.y = 35;
					snakeRect.w = 70;
					snakeRect.h = 70;
					snakeRect.y = clearY + 90 - interspaceAdd;
					snakeRect.x = clearX - 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);
					snakeRect.x = clearX + 17;
					SDL_RenderCopyEx(Render, eyeTexture, NULL, &snakeRect, result, &snakePoint, (SDL_RendererFlip)0);
					if (isNear == true)
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) - openSize / 2);
							moutchRect.y = (((y - 1) * 70 + 185) + openSize / 2) - interspaceAdd - 15;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize < 70)
							{
								openSize += 10;
							};

							oldTimeMountch = SDL_GetTicks();
						};

						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, -90, &snakePoint, (SDL_RendererFlip)0);
					}
					else
					{
						if (SDL_GetTicks() > oldTimeMountch + 10)
						{
							moutchRect;
							moutchRect.x = (((x - 1) * 70 + 85) - openSize / 2);
							moutchRect.y = (((y - 1) * 70 + 185) + openSize / 2) - interspaceAdd - 15;
							moutchRect.w = openSize;
							moutchRect.h = openSize;
							if (openSize > 0)
							{
								openSize -= 2;
							};
							if (openSize == 30)
							{
								openSize = 0;
							}
							oldTimeMountch = SDL_GetTicks();
						};
						SDL_RenderCopyEx(Render, moutchTexture, NULL, &moutchRect, -90, &snakePoint, (SDL_RendererFlip)0);
					};
				};
			}
		}
	}

	if (interspaceAdd >= 70)
	{
		interspaceAdd = 0;
		nStep = true;
	};
	if (isPause == true)
	{
		openSize = 0;
		interspaceAdd = 0;
	};
	if ((SDL_GetTicks() > (oldTimeSnake + speed))&& isPause == false)
	{
		interspaceAdd += plusInterspace;
		oldTimeSnake = SDL_GetTicks();
	};
}

bool SnakeRender::NextStep()
{
	if (nStep == true)
	{
		nStep = false;
		return true;
	}
	else
	{
		return false;
	};
}
