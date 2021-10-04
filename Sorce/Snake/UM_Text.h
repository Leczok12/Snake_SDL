#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
//#include <iostream>

class UM_Text
{
public:
	UM_Text()
	{
		oldSize = 0;
		font = NULL;
		uColor = {255,255,255,255};
		surface = NULL;
		text = NULL;
		rText = {0,0,0,0};
		oldTime = SDL_GetTicks();
	}

	~UM_Text()
	{
		SDL_DestroyTexture(text);
		TTF_CloseFont(font); 
	}

	void Load()
	{
		TTF_Init();
	}
	void createText(SDL_Renderer* Render, int size, const char* fontToLoad, const char* Text, Uint8 R, Uint8 G, Uint8 B, Uint8 A = 255)
	{
		uColor.a = A;
		uColor.r = R;
		uColor.g = G;
		uColor.b = B;
		font = TTF_OpenFont(fontToLoad, size);
		surface = TTF_RenderText_Solid(font, Text, uColor);
		text = SDL_CreateTextureFromSurface(Render, surface);
		SDL_FreeSurface(surface);
	}
	void dynamicText(int x, int y, int alpha, const char* Text, SDL_Renderer* Render, Uint8 R, Uint8 G, Uint8 B, Uint8 A = 255,int w = 0,int h = 0)
	{
		rText.x = x;
		rText.y = y;
		if (w == 0)
		{
			SDL_QueryTexture(text, NULL, NULL, &rText.w, &rText.h);
		}
		else
		{
			SDL_QueryTexture(text, NULL, NULL, &rText.w, &rText.h);
			rText.w = w;
			rText.h = h;
		};
		
		uColor.a = A;
		uColor.r = R;
		uColor.g = G;
		uColor.b = B;
		if ((oldTime + 10) <= SDL_GetTicks())
		{
			SDL_DestroyTexture(text);
			surface = TTF_RenderText_Solid(font, Text, uColor);
			text = SDL_CreateTextureFromSurface(Render, surface);
			SDL_FreeSurface(surface);
			oldTime = SDL_GetTicks();
		};
		SDL_SetTextureAlphaMod(text, alpha);
		SDL_RenderCopy(Render, text, NULL, &rText);
	}
	void showText(int x, int y, int alpha,SDL_Renderer* Render)
	{
		rText.x = x;
		rText.y = y;
		SDL_QueryTexture(text, NULL, NULL, &rText.w, &rText.h);
		SDL_SetTextureAlphaMod(text, alpha);
		SDL_RenderCopy(Render, text, NULL, &rText);
	}

private:
	int oldSize;
	Uint32 oldTime;
	TTF_Font* font;
	SDL_Color uColor;
	SDL_Surface* surface;
	SDL_Texture* text;
	SDL_Rect rText; 
};

