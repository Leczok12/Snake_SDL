#pragma once
#include <SDL.h>
#include <math.h>
#include <iostream>
#pragma once

class SnakeRender
{
public:
	SnakeRender(Uint32 sSpeed=10,int add=10);
	~SnakeRender();

	void RSnake(SDL_Renderer* Render, SDL_Texture* headTexture, SDL_Texture* tailTexture, SDL_Texture* bodyTexture, SDL_Texture* eyesTexture, SDL_Texture* eyeTexture, SDL_Texture* moutchTexture, int YXNumArray[12][12],int lenght, bool isPause);
	void SetSpeed(int speedMode);
	void SetShowSkeleton();
	bool NextStep();

private:
	SDL_Rect snakeRect;
	SDL_Rect moutchRect;
	SDL_Point snakePoint; 
	bool nStep, skeletonMode, isNear;
	Uint32 speed, oldTimeSnake, oldTimeskeletonMode, oldTimeMountch;
	int interspaceAdd, plusInterspace, appleX, appleY, openSize;
	long double param, result;
};