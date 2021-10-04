#include <SDL.h>
#include "TextureMenager.h"
#pragma once

class UM_Bar
{
public:

	UM_Bar()
	{
		sizeMultiplier = 0;
		pixelJamp = 0;
		maxValue = 0;
		value = 0;
		xPos = 0;
		yPos = 0;
		WRect = { 0,0,0,0 };
		WDRect = { 0,0,0,0 };
		ARect = { 0,0,0,0 };
		DRect = { 0,0,0,0 };
		active = false;
		press = false;
	}

	~UM_Bar()
	{

	}

	void createBar(int x, int y, float maxV,float multipler, SDL_Renderer* Render)
	{
		sizeMultiplier = multipler;
		xPos = x;
		yPos = y;
		maxValue = maxV;
		pixelJamp = 340 / maxV;
		White_Bar.LoadTexture(Render, "Textures/white_bar.png", "PNG");
		Grey_Bar.LoadTexture(Render, "Textures/grey_bar.png", "PNG");
		Dot_Bar.LoadTexture(Render, "Textures/dot_bar.png", "PNG");
		ARect = { x,y,350,10 };
		DRect = { x+340,y,10,10 };
		WRect = { x ,y, 350,10 };
		WDRect = { 0 ,0, 350,10 };
	}

	void renderBar(SDL_Renderer* R)
	{
		SDL_RenderCopy(R, Grey_Bar.ReturnTexture(), NULL, &ARect);
		SDL_RenderCopy(R, White_Bar.ReturnTexture(), &WDRect, &WRect);
		SDL_RenderCopy(R, Dot_Bar.ReturnTexture(), NULL, &DRect);
		changeValue();
	}

	void setAtive(bool a)
	{
		active = a;
	}

	void setValue(int v)
	{
		value = v;
	}

	void changeValue()
	{
		if (press == true)
		{
			int mXPos, mYPos;
			SDL_GetMouseState(&mXPos, &mYPos);
			mXPos *= 1/sizeMultiplier;
			mYPos *= 1/sizeMultiplier;
			if ((mXPos > xPos) && (mXPos < xPos + 340))
			{
				DRect = { mXPos,yPos,10,10 };
				WDRect = { 0,0,mXPos - xPos + 5,10 };
				WRect = { xPos,yPos,mXPos - xPos + 5,10 };
			}
			else if (mXPos > xPos + 340)
			{
				DRect = { xPos + 340,yPos,10,10 };
				WDRect = { 0,0, 345,10 };
				WRect = { xPos,yPos,345,10 };
			}
			else if (mXPos < xPos + 5)
			{
				DRect = { xPos ,yPos,10,10 };
				WDRect = { 0,0, 5,10 };
				WRect = { xPos,yPos,5,10 };
			};
			value = (DRect.x - xPos) / pixelJamp;
			DRect.x = (pixelJamp * value) + xPos;
			WDRect.w = (pixelJamp * value) + 5;
			WRect.w = (pixelJamp * value) + 5;
		}
		else
		{
			DRect.x = (pixelJamp * value) + xPos;
			WDRect.w = (pixelJamp * value) + 5;
			WRect.w = (pixelJamp * value) + 5;
		}
	}

	void isPress(bool c)
	{
		press = c;
	}

	bool controlBar()
	{
		int mXPos, mYPos;
		SDL_GetMouseState(&mXPos, &mYPos);
		if(((mXPos >= DRect.x * sizeMultiplier) && (mXPos <= DRect.x * sizeMultiplier + DRect.w * sizeMultiplier)) && ((mYPos >= DRect.y * sizeMultiplier) && (mYPos <= DRect.y * sizeMultiplier + DRect.h * sizeMultiplier)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isActive()
	{
		return active;
	}

	int returnValue()
	{
		return value;
	}

private:
	bool active, press;
	float pixelJamp, sizeMultiplier;
	int maxValue, value, xPos, yPos;
	TextureMenager White_Bar, Grey_Bar, Dot_Bar;
	SDL_Rect WRect;
	SDL_Rect WDRect;
	SDL_Rect ARect;
	SDL_Rect DRect;
};