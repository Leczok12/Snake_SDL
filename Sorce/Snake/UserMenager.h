#pragma once
#include <SDL.h>
#include <sstream>
#include "TextureMenager.h"
#include "UM_Button.h"
#include "UM_Text.h"
#include "Timer_Menager.h"
#include "UM_Bar.h"

using namespace std;

class UserMenager
{
public:
	UserMenager();
	~UserMenager();
	void sendMessage(const char* MSG);
	void loop();
	void RGui(SDL_Renderer* Render, UM_Button* UMB_Play, UM_Button* UMB_Set, UM_Button* UMB_Back, UM_Bar* volume, UM_Bar* speed, SDL_Texture* tVolume, SDL_Texture* tSpeed);
	void RStat(SDL_Renderer* Render, SDL_Texture* Apple, SDL_Texture* Cup, int score);

	void GameOver(SDL_Renderer* Render, UM_Button* UMB_Play, UM_Button* UMB_Set,  UM_Button* UMB_Back, UM_Bar* volume, UM_Bar* speed, SDL_Texture* tVolume, SDL_Texture* tSpeed);
	void Start(SDL_Renderer* Render, SDL_Texture* start);

	void LoadTextures(SDL_Renderer* Render);
	void SetShowTimer();
	bool CheckPause();
	bool CheckReset();
	bool CheckSet();
private:
	Timer_Menager TimerM;
	TextureMenager TM_BackGround;
	UM_Text UMT_END, UMT_SCORE, UMT_SETTINGS, UMT_SCORE_TITLE, UMT_SCORE_MAIN, UMT_TIME_MAIN, UMT_TIME, UMT_TIME_TITLE, UMT_BEST_SCORE, UMT_START, UMT_WIN;
	SDL_Rect AppleRect;
	SDL_Rect pauseRect;
	SDL_Rect CupRect;

	const char* MSG;
	bool gloablPause, reset, isPause, isSet, showMainTimer,isFirst,isFirstText ,  isWin;
	unsigned int OldTime,OldTimeSetTimer;
	int alpha, scorePrivate;
	Uint8 startAlpha;
	Uint32 oldTimeStart;

	int bestScore;

};