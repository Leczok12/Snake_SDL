#include "AppleObject.h"

AppleObject::AppleObject(int wWidth,int hHeight,int nNumberOfSeries ,int iInterspace ,int speed)
{
	appleRect.x = -100;
	appleRect.y = -100;
	appleRect.w = wWidth;
	appleRect.h = hHeight;

	width = wWidth;
	height = hHeight;

	applePoint.x = wWidth/2;
	applePoint.y = hHeight/2;

	interspace = iInterspace;
	interspaceAdd = 0;
	series = 0;
	oldX = 0;
	oldY = 0;
	numberOfSeries = nNumberOfSeries;
	intertimeBetweenSeries = speed;
	aplleGrow = true;
	newLocation = false;
	newL = false;
	oldTimeApple = SDL_GetTicks();

	howIsFree = 0;
}

AppleObject::~AppleObject()
{

}

void AppleObject::RAte(SDL_Renderer* Render, SDL_Texture* texture)
{
	for (int i = 0; i < 10; i++)
	{
		EA[i].Show(Render,texture,0);
	}
}

void AppleObject::updateAte()
{
	howIsFree = 10;
	for (int i = 0; i < 10; i++)
	{
		EA[i].cycleUp();
		if (EA[i].free()==true)
		{
			howIsFree--;
		}
	}
}

void AppleObject::ateReset()
{
	for (int i = 0; i < 10; i++)
	{
		EA[i].reste();
	}
	oldX = 0;
	oldY = 0;
}

void AppleObject::RApple(SDL_Renderer* Render, SDL_Texture* texture, int YXPosArray[12][12],int lenght)
{
	int XNumPos = 0, YNumPos = 0;
	
	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x < 11; x++)
		{
			if (YXPosArray[y][x] == 420)
			{
				XNumPos = x;
				YNumPos = y;
			};
		};
	};

	if ((XNumPos != oldX) || (YNumPos != oldY))// && (newL== false))
	{
		EA[howIsFree].set(oldY, oldX, lenght);
		newLocation = true;
		interspaceAdd = 0;
		series = 0;
		appleRect.x = (XNumPos - 1) * 70 + 84;
		appleRect.y = (YNumPos - 1) * 70 + 184;
		appleRect.w = 2;
		appleRect.h = 2;
		oldX = XNumPos;
		oldY = YNumPos;
	};

	if (newLocation == true) //new location animation
	{
		if (SDL_GetTicks() > (oldTimeApple + 10))
		{
			newL = true;
			appleRect.x -= 2;
			appleRect.y -= 2;
			appleRect.w += 4;
			appleRect.h += 4;

			if ((appleRect.w >= width))
			{
				appleRect.w = width;
				appleRect.h = height;
				aplleGrow = true;
				newLocation = false;
				newL = false;
			};
			oldTimeApple = SDL_GetTicks();
		};
	}
	else // pulse animation
	{
		if ((XNumPos > 0) && (YNumPos > 0))
		{
			if (SDL_GetTicks() > (oldTimeApple + intertimeBetweenSeries))
			{
				appleRect.x = (XNumPos - 1) * 70 + 50;
				appleRect.y = (YNumPos - 1) * 70 + 150;
				if (aplleGrow == true)
				{
					interspaceAdd += interspace;

					appleRect.x -= interspaceAdd / 2;
					appleRect.y -= interspaceAdd / 2;
					appleRect.w += interspace;
					appleRect.h += interspace;

					if (series == numberOfSeries)
					{
						aplleGrow = false;
						series = 0;
					}
					series++;
				}
				else
				{
					interspaceAdd -= interspace;

					appleRect.x -= interspaceAdd / 2;
					appleRect.y -= interspaceAdd / 2;
					appleRect.w -= interspace;
					appleRect.h -= interspace;

					if (series == numberOfSeries)
					{
						aplleGrow = true;
						series = 0;
					}
					series++;
				};

				applePoint.x = appleRect.x / 2;
				applePoint.y = appleRect.y / 2;

				oldTimeApple = SDL_GetTicks();
			};
		};
	};
	if ((appleRect.x > 30) && (appleRect.y > 130))
	{
		SDL_RenderCopyEx(Render, texture, NULL, &appleRect, 0, &applePoint, (SDL_RendererFlip)0);
	};
	
}