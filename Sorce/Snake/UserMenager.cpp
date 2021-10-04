#include "UserMenager.h"
#include <SDL.h>

UserMenager::UserMenager()
{
	isPause = true;
	isSet = false;
	reset = true;
	MSG = nullptr;
	alpha = 0;
	OldTime = 0;
	OldTimeSetTimer = 0;
	gloablPause = false;
	showMainTimer = false;
	isFirst = true;
	isWin = false;
	isFirstText = true;
	scorePrivate = 0;

	bestScore = 0;

	pauseRect.w = 452;
	pauseRect.h = 452;
	pauseRect.x = 172;
	pauseRect.y = 224;

	AppleRect.w = 70;
	AppleRect.h = 70;
	AppleRect.x = 50;
	AppleRect.y = 40;

	CupRect.w = 70;
	CupRect.h = 70;
	CupRect.x = 200;
	CupRect.y = 40;

	startAlpha = 255;
	oldTimeStart = 0;

	UMT_END.Load(); 
	UMT_SCORE.Load(); 
	UMT_BEST_SCORE.Load();
	UMT_SETTINGS.Load(); 
	UMT_SCORE_TITLE.Load();
	UMT_SCORE_MAIN.Load();
	UMT_TIME_MAIN.Load();
	UMT_TIME.Load();
	UMT_TIME_TITLE.Load();
	UMT_START.Load();
	UMT_WIN.Load();
}

UserMenager::~UserMenager()
{

}

void UserMenager::sendMessage(const char* sentMSG)
{
	MSG = sentMSG;
	if ((MSG == "ESC") || (MSG == "END"))
	{
		isPause = true;
	}
	else if (MSG == "SPACE")
	{
		if (isFirst == true)
		{
			isFirst = false;
			SDL_Delay(200);
		}
		else
		{
			if ((isPause == true) && (isSet == false))
			{
				isPause = false;
				reset = true;
			}
			else if ((isPause == true) && (isSet == true))
			{
				isPause = true;
				isSet = false;
			};
		};
	}
	else if (MSG == "SETTINGS")
	{
		if (isPause == true)
		{
			isSet = true;
		};
	}
	MSG = nullptr;
}

void UserMenager::loop()
{
	reset = false;
}

void UserMenager::RGui(SDL_Renderer* Render, UM_Button* UMB_Play, UM_Button* UMB_Set, UM_Button* UMB_Back, UM_Bar* volume, UM_Bar* speed, SDL_Texture* tVolume, SDL_Texture* tSpeed)
{
	GameOver(Render, UMB_Play, UMB_Set,UMB_Back,volume,speed,tVolume,tSpeed);
}

void UserMenager::RStat(SDL_Renderer* Render, SDL_Texture* Apple, SDL_Texture* Cup, int score)
{
	SDL_RenderCopy(Render, Apple, NULL, &AppleRect);
	SDL_RenderCopy(Render, Cup, NULL, &CupRect);

	scorePrivate = score;
	stringstream scoreToString;
	scoreToString << score - 3;
	string scoreToChar = scoreToString.str();
	const char* scoreChar_1 = (char*)scoreToChar.c_str();
	UMT_SCORE_MAIN.dynamicText(120, 38, 255, scoreChar_1, Render, 255, 255, 255);

	if (bestScore < (score - 3))
	{
		bestScore = score - 3;
	};
	stringstream bestScoreToString;
	bestScoreToString << bestScore;
	string bestScoreToChar = bestScoreToString.str();
	const char* scoreChar_2 = (char*)bestScoreToChar.c_str();
	UMT_BEST_SCORE.dynamicText(270, 38, 255, scoreChar_2, Render, 255, 255, 255);
	if (showMainTimer == true)
	{
		UMT_TIME_MAIN.dynamicText(286, 100, 255, TimerM.returnClock(), Render, 255, 255, 255, 255, 228, 54);
	};
	if (((score - 3) == 97)&&(isWin != true))
	{
		isPause = true;
		gloablPause = true;
		isWin = true;
	};
}

void UserMenager::Start(SDL_Renderer* Render, SDL_Texture* start)
{
	SDL_Rect startRect = { 0,0,800,900 };
	if (isFirst == true)
	{
		//SDL_RenderCopy(Render, start, NULL, &startRect);
	}
	else
	{
		if (startAlpha != 0)
		{
			if (SDL_GetTicks() > oldTimeStart + 2)
			{
				startAlpha -= 5;
				oldTimeStart = SDL_GetTicks();
			}
			SDL_SetTextureAlphaMod(start, startAlpha);
			//SDL_RenderCopy(Render, start, NULL, &startRect);
		};
	}
}

void UserMenager::GameOver(SDL_Renderer* Render, UM_Button* UMB_Play, UM_Button* UMB_Set, UM_Button* UMB_Back,UM_Bar *volume, UM_Bar* speed, SDL_Texture* tVolume, SDL_Texture* tSpeed)
{
	if (isPause == true)
	{
		if (isSet == true)
		{
			gloablPause = true;

			SDL_RenderCopy(Render, TM_BackGround.ReturnTexture(), NULL, &pauseRect);
			UMT_SETTINGS.showText(233, 250, alpha, Render);
			SDL_Rect Rect = { 385,405,30,30 };
			SDL_RenderCopy(Render,	tVolume, NULL, &Rect);
			Rect = { 385,345,30,30 };
			SDL_RenderCopy(Render,	tSpeed, NULL, &Rect);
			volume->renderBar(Render);
			volume->setAtive(true);
			speed->renderBar(Render);
			speed->setAtive(true);
			UMB_Back->renderButton(Render, alpha);
			UMB_Back->setActive(true);
			UMB_Set->setActive(false);
			UMB_Play->setActive(false);
		}
		else
		{
			volume->setAtive(false);
			speed->setAtive(false);
			TimerM.stop();
			gloablPause = true;

			if ((SDL_GetTicks() > OldTime + 6))
			{
				if (alpha < 255)
				{
					alpha += 5;
					UMB_Set->setActive(false);
					UMB_Play->setActive(false);
					UMB_Back->setActive(false);
				}
				else
				{
					UMB_Set->setActive(true);
					UMB_Play->setActive(true);
					UMB_Back->setActive(false);
					alpha = 255;
				};
				OldTime = SDL_GetTicks();
			};

			SDL_SetTextureAlphaMod(TM_BackGround.ReturnTexture(), alpha);
			SDL_RenderCopy(Render, TM_BackGround.ReturnTexture(), NULL, &pauseRect);
			UMB_Play->renderButton(Render, alpha);
			UMB_Set->renderButton(Render, alpha);
			
			stringstream scoreToString;
			scoreToString << scorePrivate - 3;
			string scoreToChar = scoreToString.str();
			const char* scoreChar = (char*)scoreToChar.c_str();
			if (isFirstText == true)
			{
				UMT_START.showText(300, 250, alpha, Render);
			}
			else if (isWin == true)
			{
				UMT_WIN.showText(265, 250, alpha, Render);
				UMT_TIME.dynamicText(350, 370, alpha, TimerM.returnClock(), Render, 255, 255, 255);
				UMT_TIME_TITLE.showText(240, 370, alpha, Render);
			}
			else
			{
				UMT_END.showText(300, 250, alpha, Render);
				UMT_SCORE_TITLE.showText(311, 370, alpha, Render);
				UMT_SCORE.dynamicText(451, 370, alpha, scoreChar, Render, 255, 255, 255);
				UMT_TIME.dynamicText(350, 430, alpha, TimerM.returnClock(), Render, 255, 255, 255);
				UMT_TIME_TITLE.showText(240, 430, alpha, Render);
			};
			

		};
	}
	else if (isPause == false)
	{
		if ((SDL_GetTicks() > OldTime + 6))
		{
			if (alpha > 0)
			{
				alpha -= 5;
				if (alpha>1)
				{
					TimerM.start();
				}
			}
			else
			{
				isFirstText = false;
				isWin = false;
				alpha = 0;
				gloablPause = false;
			};
			OldTime = SDL_GetTicks();
		};

		SDL_SetTextureAlphaMod(TM_BackGround.ReturnTexture(), alpha);
		SDL_RenderCopy(Render, TM_BackGround.ReturnTexture(), NULL, &pauseRect);
		UMB_Back->setActive(false);
		UMB_Play->setActive(false);
		UMB_Play->renderButton(Render, alpha);
		UMB_Set->setActive(false);
		UMB_Set->renderButton(Render, alpha);
		
		stringstream scoreToString;
		scoreToString << scorePrivate - 3;
		string scoreToChar = scoreToString.str();
		const char* scoreChar = (char*)scoreToChar.c_str();
		if (isFirstText == true)
		{
			UMT_START.showText(300, 250, alpha, Render);
		}
		else if (isWin == true)
		{
			UMT_WIN.showText(265, 250, alpha, Render);
			UMT_TIME.dynamicText(350, 370, alpha, TimerM.returnClock(), Render, 255, 255, 255);
			UMT_TIME_TITLE.showText(240, 370, alpha, Render);
		}
		else
		{
			UMT_END.showText(300, 250, alpha, Render);
			UMT_SCORE_TITLE.showText(311, 370, alpha, Render);
			UMT_SCORE.dynamicText(451, 370, alpha, scoreChar, Render, 255, 255, 255);
			UMT_TIME.dynamicText(350, 430, alpha, TimerM.returnClock(), Render, 255, 255, 255);
			UMT_TIME_TITLE.showText(240, 430, alpha, Render);
		};
	};
}


void UserMenager::LoadTextures(SDL_Renderer* Render)
{
	UMT_END.createText(Render, 58, "font.ttf", "KONIEC", 255, 255, 255);
	UMT_SCORE.createText(Render, 40, "font.ttf", "0", 255, 255, 255);
	UMT_SETTINGS.createText(Render, 58, "font.ttf", "USTAWIENIA", 255, 255, 255);
	UMT_SCORE_TITLE.createText(Render, 40, "font.ttf", "Wynik :", 255, 255, 255);
	UMT_SCORE_MAIN.createText(Render, 60, "font.ttf", "0", 255, 255, 255);
	UMT_BEST_SCORE.createText(Render, 60, "font.ttf", "0", 255, 255, 255);
	UMT_TIME_MAIN.createText(Render, 80, "helper_font.ttf", "00:00:00:0", 255, 255, 255);
	UMT_TIME.createText(Render, 40, "font.ttf", "00:00:00:0", 255, 255, 255);
	UMT_TIME_TITLE.createText(Render, 40, "font.ttf", "Czas :", 255, 255, 255);
	UMT_START.createText(Render, 58, "font.ttf", "WITAJ!!!", 255, 255, 255);
	UMT_WIN.createText(Render, 58, "font.ttf", "WYGRANA", 255, 255, 255);
	TM_BackGround.LoadTexture(Render, "Textures/Gui_Background.png", "PNG");
	
}

void UserMenager::SetShowTimer()
{
	if (SDL_GetTicks() > (OldTimeSetTimer + 200))
	{
		if (showMainTimer == false)
		{
			showMainTimer = true;
		}
		else
		{
			showMainTimer = false;
		};
		OldTimeSetTimer = SDL_GetTicks();
	};
}

bool UserMenager::CheckPause()
{
	return gloablPause;
}

bool UserMenager::CheckReset() 
{
	return reset;
}

bool UserMenager::CheckSet()
{
	return isSet;
}