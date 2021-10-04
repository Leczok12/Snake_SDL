#pragma once
#include <SDL.h>
#include "AudioMenager.h"
class HitAnimation
{
public:
	HitAnimation() 
	{
		dest = { 0,0,210,210 };
		show = { 0,0,210,210 };
		point = { 105,105 };
		oldTime = 0;
		cycle = 0;
		back = false;
	};
	~HitAnimation()
	{

	};
	void Show(SDL_Renderer* R, SDL_Texture* T,AudioMenager *A,int flip,int x,int y)
	{
		if (SDL_GetTicks() > oldTime + 2 )
		{
			if ((cycle == 0) && (back == false))
			{
				A->play();
			};
			
			dest.x = 210 * cycle;
			oldTime = SDL_GetTicks();
			
			if ((cycle == 10)&&(back==false))
			{
				cycle = 10;
				back = true;
			}
			else if (back == true)
			{
				if (cycle == 0)
				{
					cycle = 0;
				}
				else
				{
					cycle--;
				};
			}
			else
			{
				cycle++;
			};
		}
		show.x = x;
		show.y = y;
		SDL_RenderCopyEx(R, T, &dest, &show, flip, &point,(SDL_RendererFlip)0);
	}
	void reset()
	{
		cycle = 0;
		back = false;
	};

private:
	SDL_Rect dest;
	SDL_Rect show;
	SDL_Point point;

	Uint32 oldTime;
	int cycle;
	bool back;
};
