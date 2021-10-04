#include "TextureMenager.h"

TextureMenager::TextureMenager()
{
	texture = nullptr;
	surface = nullptr;

	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;

	point.x = 0;
	point.y = 0;
}

TextureMenager::~TextureMenager()
{
	SDL_DestroyTexture(texture);
}

void TextureMenager::LoadTexture(SDL_Renderer* Render, const char* src, const char* mode)
{
	if (mode == "JPG")
	{
		IMG_Init(IMG_INIT_JPG);
		surface = IMG_Load(src);
		texture = SDL_CreateTextureFromSurface(Render, surface);
		SDL_FreeSurface(surface);
		
	}
	else if (mode == "BMP")
	{
		surface = IMG_Load(src);
		texture = SDL_CreateTextureFromSurface(Render, surface);
		SDL_FreeSurface(surface);
	}
	else if (mode == "PNG")
	{
		IMG_Init(IMG_INIT_PNG);
		surface = IMG_Load(src);
		texture = SDL_CreateTextureFromSurface(Render, surface);
		SDL_FreeSurface(surface);
	}

	
}

void TextureMenager::RenderTexture(SDL_Renderer* Render, int x, int y, int width, int height, int rotation,int rotationPointX , int rotationPointY )
{
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	if (rotationPointX==-1)
	{
		point.x = width / 2;
	}
	else
	{
		point.x = rotationPointX;
	}

	if (rotationPointY == -1)
	{
		point.y = height / 2;
	}
	else
	{
		point.y = rotationPointY;
	}

	SDL_RenderCopyEx(Render, texture, NULL, &rect, rotation, &point, (SDL_RendererFlip)0);
};

SDL_Texture* TextureMenager::ReturnTexture()
{
	return texture;
};