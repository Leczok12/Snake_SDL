#pragma once
#include <SDL.h>
class EatAnimation
{
public:
	EatAnimation()
	{
		dest = { 0,0,70,70 };
		show = { 0,0,70,70 };
		point = { 35,35 };
		isFree = true;
		cycle = 10;
		lenght = 0;
	};

	~EatAnimation()
	{

	};

	void cycleUp()
	{
		if (cycle<10)
		{
			if (cycle > 0)
			{
				if ((lenght == 3)||(lenght == 4))
				{
					cycle+=4;
				}
				if ((lenght == 5) || (lenght == 6))
				{
					cycle += 3;
				}
				if ((lenght >= 7) || (lenght < 10))
				{
					cycle += 2;
				}
				else
				{
					cycle++;
				}
			}
			else
			{
				cycle++;
			};
		}
		else
		{
			isFree = true;
			cycle = 10;
		}
	};

	void reste()
	{
		cycle = 10;
	}

	void set(int y, int x, int lLenght)
	{
		lenght = lLenght;
		isFree = false;
		show.x = (x - 1) * 70 + 50;
		show.y = (y - 1) * 70 +150;
		cycle = 0;
	}
	void Show(SDL_Renderer* R, SDL_Texture* T, int flip)
	{
		if((isFree == false)&&(show.y>149)&&(show.x>49))
		{
			dest.x = 70 * cycle;
			dest.y = 0;
			SDL_RenderCopyEx(R, T, &dest, &show, flip, &point, (SDL_RendererFlip)0);
		};
	}
	bool free()
	{
		return isFree;
	}

private:
	SDL_Rect dest;
	SDL_Rect show;
	SDL_Point point;
	int cycle, lenght;
	bool isFree;
};