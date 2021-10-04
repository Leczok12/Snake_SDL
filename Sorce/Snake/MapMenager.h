#pragma once
#include <SDL.h>
#include "AudioMenager.h"
#include "HitAnimation.h"
#include <iostream>

#define EMPTY_SPACE 0
#define NOT_ALLOWED_SPACE 999
#define APPLE 420

class MapMenager
{
public:
	MapMenager(int yxYXpos = 0, int sSide = 3, int oOldSide = 3, int lLenght = 3);
	~MapMenager();

	void updatePos(AudioMenager* AU);
	void reset();
	void sideChange(int,AudioMenager* AU,bool pause); // 1 - up, 2 - left, 3 - right, 4 - down 
	void snakeControl(bool);
	void newApple(AudioMenager* AU);
	void renderCrash(SDL_Renderer* R, SDL_Texture* T, AudioMenager* AU);
	bool checkError();

	int YXposNUM[12][12];
	int length;

private:
	HitAnimation HM;
	bool globalError;

	int side;
	int oldSide;
};

