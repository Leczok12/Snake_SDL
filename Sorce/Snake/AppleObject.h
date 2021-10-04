#pragma once
#include <SDL.h>
#include "EatAnimation.h"

class AppleObject
{
public:
	AppleObject(int width = 70, int height = 70, int nNumberOfSeries = 10, int iInterspace = 2, int speed = 70);
	~AppleObject();
	void RApple(SDL_Renderer* Render, SDL_Texture* texture, int YXPosArray[12][12],int lenght);
	void RAte(SDL_Renderer* Render, SDL_Texture* texture);
	void ateReset();
	void updateAte();

private:
	SDL_Rect appleRect;
	SDL_Point applePoint;
	int interspace, interspaceAdd, numberOfSeries, oldX, oldY, width, height;
	unsigned int series;
	bool aplleGrow, newLocation,newL;
	Uint32 intertimeBetweenSeries;
	Uint32 oldTimeApple;

	EatAnimation EA[10];
	int howIsFree;
};