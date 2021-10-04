#pragma once
#include <SDL.h>
#include "TextureMenager.h"
#include "SnakeRender.h"
#include "AppleObject.h"
#include "MapMenager.h"
#include "UserMenager.h"
#include "UM_Button.h"
#include "AudioMenager.h"
#include "HitAnimation.h"
#include "AutoSet.h"
#include "UM_Bar.h"

class GameMain
{
public:
	GameMain(const char* title, int width, int height);
	~GameMain();
	void RenderClear();
	void MsgLoop();
	void Render();
	bool RunReturn();

private:
	float sizeMultiplier;
	int FPS;
	int gameWindowWidth;
	int gameWindowHeight;
	bool run;
	Uint32 oldTime;
	SDL_Window* gameWindow;
	SDL_Renderer* gameRender;
	SDL_Event msg;

	SnakeRender SR;

	AppleObject AO_Aplle;

	MapMenager MM;

	UserMenager UM;

	TextureMenager TM_Board;
	TextureMenager TM_Apple;
	TextureMenager TM_Dot;
	TextureMenager TM_BackGround;
	TextureMenager TM_SnakeHead;
	TextureMenager TM_SnakeEyes;
	TextureMenager TM_SnakeEye;
	TextureMenager TM_SnakeBody;
	TextureMenager TM_SnakeMoutch;
	TextureMenager TM_SnakeHit;
	TextureMenager TM_PlayButton;
	TextureMenager TM_SettingsButton;
	TextureMenager TM_BackButton;
	TextureMenager TM_CloseButton_1;
	TextureMenager TM_CloseButton_2;
	TextureMenager TM_Cup;
	TextureMenager TM_Start;
	TextureMenager TM_OnButton;
	TextureMenager TM_OffButton;
	TextureMenager TM_Speed;
	TextureMenager TM_Volume;
	TextureMenager TM_Eat_Animation;

	UM_Button UMB_Play;
	UM_Button UMB_Settings;
	UM_Button UMB_Back;
	UM_Button UMB_Close;
	UM_Button UMB_SoundOff;
	UM_Button UMB_SoundOn;

	AudioMenager AU_Button;
	AudioMenager AU_Snake_up;
	AudioMenager AU_Snake_down;
	AudioMenager AU_Snake_left;
	AudioMenager AU_Snake_right;
	AudioMenager AU_Snake_ate;
	AudioMenager AU_Snake_crash;

	UM_Bar UMBa_Volume;
	UM_Bar UMBa_Speed;

	AutoSet AS;
};