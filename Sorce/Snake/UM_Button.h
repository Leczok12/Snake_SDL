#pragma once
#include <SDL.h>
#include <iostream>

class UM_Button
{
private:
	int PosX, PosY, ButtonWidth, ButtonHeight, hoverAlpha;
	float sizeMultiplier;
	bool Press, Active;
	Uint32 oldTime,oldTimePress;
	SDL_Texture* ButtonTexture;
	SDL_Texture* ButtonHoverTexture;
public:
	UM_Button()
	{
		oldTime = 0;
		oldTimePress = 0;
		hoverAlpha = 0;
		PosX = 0;
		PosY = 0; 
		ButtonWidth = 0;
		ButtonHeight = 0;
		Press = false;
		Active = false;
		ButtonTexture = nullptr;
		ButtonHoverTexture = nullptr;
	}
	~UM_Button()
	{}
	bool isActive()
	{
		return Active;
	}
	void setActive(bool A)
	{
		Active = A;
	}
	void createButton(int x, int y, int width, int height, float multipler, SDL_Texture* texture, SDL_Texture* hoverTexture = nullptr)
	{
		sizeMultiplier = multipler;
		PosX = x;
		PosY = y;
		ButtonWidth = width;
		ButtonHeight = height;
		ButtonTexture = texture;
		if (hoverTexture != nullptr)
		{
			ButtonHoverTexture = hoverTexture;
		};
	}
	void renderButton(SDL_Renderer* Render, int alpha)
	{
		SDL_Rect buttonRect;
		buttonRect.x = PosX;
		buttonRect.y = PosY;
		buttonRect.w = ButtonWidth;
		buttonRect.h = ButtonHeight;
		SDL_SetTextureAlphaMod(ButtonTexture, alpha);
		SDL_RenderCopy(Render, ButtonTexture, NULL, &buttonRect);
		int mXPos, mYPos;
		SDL_GetMouseState(&mXPos, &mYPos);
		if ((((mXPos >= (PosX * sizeMultiplier)) && (mXPos <= (PosX * sizeMultiplier + ButtonWidth * sizeMultiplier))) && ((mYPos >= (PosY * sizeMultiplier)) && (mYPos <= (PosY * sizeMultiplier + ButtonHeight * sizeMultiplier)))) && (ButtonHoverTexture != nullptr))
		{
			if (SDL_GetTicks() > (oldTime + 2))
			{
				if (hoverAlpha < 255)
				{
					hoverAlpha += 17;
				}
				else
				{
					hoverAlpha = 255;
				};
				oldTime = SDL_GetTicks();
			};
			SDL_SetTextureAlphaMod(ButtonHoverTexture, hoverAlpha);
			SDL_RenderCopy(Render, ButtonHoverTexture, NULL, &buttonRect);
		}
		else
		{
			if (SDL_GetTicks() > (oldTime + 2))
			{

				if (hoverAlpha > 0)
				{
					hoverAlpha -= 17;
				}
				else
				{
					hoverAlpha = 0;
				};
				oldTime = SDL_GetTicks();
			};
			SDL_SetTextureAlphaMod(ButtonHoverTexture, hoverAlpha);
			SDL_RenderCopy(Render, ButtonHoverTexture, NULL, &buttonRect);
		};
		
	}
	bool controlButton()
	{
		int mXPos, mYPos;
		SDL_GetMouseState(&mXPos, &mYPos);
		if (((mXPos >= (PosX * sizeMultiplier)) && (mXPos <= (PosX * sizeMultiplier + ButtonWidth * sizeMultiplier))) && ((mYPos >= (PosY * sizeMultiplier)) && (mYPos <= (PosY * sizeMultiplier + ButtonHeight * sizeMultiplier))))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};