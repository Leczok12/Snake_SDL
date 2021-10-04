#pragma once
#include <SDL.h>
#include <SDL_image.h>

class TextureMenager
{
public:
	TextureMenager();
	~TextureMenager();

	//RENDER :
	//	main window renderer
	//SRC:
	//	file path
	//MODE :
	//	1. mode "PNG" for file.png files
	//	2. mode "BMP" for file.bmp files
	//	3. mode "JPG" for file.jpg files
	void LoadTexture(SDL_Renderer* Render, const char* src, const char *mode);
	
	void RenderTexture(SDL_Renderer* Render, int x, int y, int width, int height, int rotation = 0, int rotationPointX = -1, int rotationPointY = -1);
	
	SDL_Texture* ReturnTexture();

private:
	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Rect rect;
	SDL_Point point;
};