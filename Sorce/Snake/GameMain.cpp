#include "GameMain.h"

GameMain::GameMain(const char* title, int width, int height)
{
	//set variables
	

	FPS = 60;
	run = true;
	gameWindowHeight = height;
	gameWindowWidth = width;
	SDL_PollEvent(&msg);
	oldTime = SDL_GetTicks();

	//create Window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	sizeMultiplier = (float)DM.h / 1080.0;

	gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * sizeMultiplier, height * sizeMultiplier, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );

	//create Render
	gameRender = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	//load Textures
	TM_Board.LoadTexture(gameRender, "Textures/Plansza.png", "PNG");
	TM_BackGround.LoadTexture(gameRender, "Textures/Background.png", "PNG");
	TM_SnakeHead.LoadTexture(gameRender, "Textures/Snake_Head.png", "PNG");
	TM_Apple.LoadTexture(gameRender, "Textures/apple.png", "PNG");
	TM_SnakeBody.LoadTexture(gameRender, "Textures/Snake_Body.png", "PNG");
	TM_Dot.LoadTexture(gameRender, "Textures/Snake_Tail.png", "PNG");
	TM_SnakeEyes.LoadTexture(gameRender, "Textures/Snake_Eyes.png", "PNG");
	TM_SnakeEye.LoadTexture(gameRender, "Textures/Snake_Eye.png", "PNG");
	TM_SnakeMoutch.LoadTexture(gameRender, "Textures/Snake_Moutch.png", "PNG");
	TM_SnakeHit.LoadTexture(gameRender, "Textures/hit_snake_texture.png", "PNG");
	TM_PlayButton.LoadTexture(gameRender, "Textures/Play_Button.png", "PNG");
	TM_SettingsButton.LoadTexture(gameRender, "Textures/Set_Button.png", "PNG");
	TM_BackButton.LoadTexture(gameRender, "Textures/Back_Button.png", "PNG");
	TM_CloseButton_1.LoadTexture(gameRender, "Textures/Close_Button_1.png", "PNG");
	TM_CloseButton_2.LoadTexture(gameRender, "Textures/Close_Button_2.png", "PNG");
	TM_Cup.LoadTexture(gameRender, "Textures/cup.png", "PNG");
	TM_Start.LoadTexture(gameRender, "Textures/Start.png", "PNG");
	TM_OnButton.LoadTexture(gameRender, "Textures/Sound_On_Button.png", "PNG");
	TM_OffButton.LoadTexture(gameRender, "Textures/Sound_Off_Button.png", "PNG");
	TM_Speed.LoadTexture(gameRender, "Textures/Speed.png", "PNG");
	TM_Volume.LoadTexture(gameRender, "Textures/Volume.png", "PNG");
	TM_Eat_Animation.LoadTexture(gameRender, "Textures/eat_snake_texture.png", "PNG");
	//load objects
	AO_Aplle = AppleObject::AppleObject(70,70,10,2,60);
	UM.LoadTextures(gameRender);

	//load buttons
	UMB_Play.createButton(190, 580, 200, 75, sizeMultiplier, TM_PlayButton.ReturnTexture());
	UMB_Settings.createButton(410, 580, 200, 75, sizeMultiplier, TM_SettingsButton.ReturnTexture());
	UMB_Back.createButton(360, 580, 75, 75, sizeMultiplier, TM_BackButton.ReturnTexture());
	UMB_Close.createButton(680, 60, 45, 45, sizeMultiplier, TM_CloseButton_1.ReturnTexture(), TM_CloseButton_2.ReturnTexture());
	UMB_Close.setActive(true);
	UMB_SoundOff.createButton(620, 60, 45, 45, sizeMultiplier, TM_OffButton.ReturnTexture());
	UMB_SoundOn.createButton(620, 60, 45, 45, sizeMultiplier, TM_OnButton.ReturnTexture());
	UMB_SoundOn.setActive(true);

	//load audio
	AU_Button.load("Audio/button_press.wav");
	AU_Snake_up.load("Audio/snake_up.wav");
	AU_Snake_down.load("Audio/snake_down.wav");
	AU_Snake_left.load("Audio/snake_left.wav");
	AU_Snake_right.load("Audio/snake_right.wav");
	AU_Snake_ate.load("Audio/snake_ate.wav");
	AU_Snake_crash.load("Audio/snake_crash.wav");
	
	//load bars
	UMBa_Volume.createBar(225, 440, 128.0, sizeMultiplier, gameRender);
	UMBa_Speed.createBar(225, 380, 5.0, sizeMultiplier, gameRender);
	
	//Auto set !!!!!!!!!!!!!!!!!!!!!!!!!
	int Sound;
	AS.Read(&UMBa_Volume, &UMBa_Speed, Sound);

	if (Sound == 0)
	{
		UMB_SoundOn.setActive(false);
		UMB_SoundOff.setActive(true);
	}
}

GameMain::~GameMain()
{
	int soundOn;
	if (UMB_SoundOn.isActive() == true)
	{
		soundOn = 1;
	}
	else
	{
		soundOn = 0;
	};
	AS.Write(UMBa_Volume.returnValue(), UMBa_Speed.returnValue(), soundOn);
	//Auto sevae !!!!!!!!!!!!!!!!!!!!!!
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRender);
}

void GameMain::MsgLoop()
{
	
	//Set Speed
	SR.SetSpeed(UMBa_Speed.returnValue());

	//Set Volume
	AU_Button.changeVolume(UMBa_Volume.returnValue());
	AU_Snake_up.changeVolume(UMBa_Volume.returnValue());
	AU_Snake_down.changeVolume(UMBa_Volume.returnValue());
	AU_Snake_left.changeVolume(UMBa_Volume.returnValue());
	AU_Snake_right.changeVolume(UMBa_Volume.returnValue());
	AU_Snake_ate.changeVolume(UMBa_Volume.returnValue());
	AU_Snake_crash.changeVolume(UMBa_Volume.returnValue());

	if (UM.CheckReset() == true)
	{
		MM.reset();
		AO_Aplle.ateReset();
	}; 
	if (MM.checkError() == true)
	{
		UM.sendMessage("END");
	};
	if ((UM.CheckPause() == false) && (SR.NextStep() == true))
	{
		AO_Aplle.updateAte();
		MM.updatePos(&AU_Snake_ate);
	};

	UM.loop();

	SDL_PollEvent(&msg);
	if ((UMBa_Volume.controlBar() == true) && (UMBa_Volume.isActive() == true) && (msg.type ==  SDL_MOUSEBUTTONDOWN))
	{
		UMBa_Volume.isPress(true);
	}
	else if (msg.type == SDL_MOUSEBUTTONUP)
	{
		UMBa_Volume.isPress(false);
	};

	if ((UMBa_Speed.controlBar() == true) && (UMBa_Speed.isActive() == true) && (msg.type == SDL_MOUSEBUTTONDOWN))
	{
		UMBa_Speed.isPress(true);
	}
	else if (msg.type == SDL_MOUSEBUTTONUP)
	{
		UMBa_Speed.isPress(false);
	};

	//Comunication loop
	switch (msg.type)
	{
	case SDL_QUIT:
		run = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (msg.button.button)
		{
		case SDL_BUTTON_LEFT:
			if ((UMB_Play.controlButton() == true) && (UMB_Play.isActive() == true))
			{
				AU_Button.play();
				UM.sendMessage("SPACE");
				SDL_Delay(100);
			};
			if ((UMB_Close.controlButton() == true) && (UMB_Close.isActive() == true))
			{
				run = false;
				SDL_Delay(100);
			};
			if ((UMB_Settings.controlButton() == true) && (UMB_Settings.isActive() == true))
			{
				AU_Button.play();
				UM.sendMessage("SETTINGS");
				SDL_Delay(100);
			};
			if ((UMB_Back.controlButton() == true) && (UMB_Back.isActive() == true))
			{
				AU_Button.play();
				UM.sendMessage("SPACE");
				SDL_Delay(100);
			};
			if ((UMB_SoundOn.controlButton() == true) && (UMB_SoundOn.isActive() == true))
			{
				SDL_Delay(100);
				UMB_SoundOn.setActive(false);
				UMB_SoundOff.setActive(true);
			}
			else if ((UMB_SoundOff.controlButton() == true) && (UMB_SoundOff.isActive() == true))
			{
				SDL_Delay(100);
				UMB_SoundOff.setActive(false);
				UMB_SoundOn.setActive(true);
			};
			break;
		default:
			UMBa_Volume.isPress(false);
			break;
		}
	case SDL_KEYDOWN:
		switch (msg.key.keysym.scancode)
		{
			case SDL_SCANCODE_F1:
				UM.SetShowTimer();
				break;
			case SDL_SCANCODE_F2:
				SR.SetShowSkeleton();
				break;
			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_W:
				MM.sideChange(1, &AU_Snake_up, UM.CheckPause());
				break;

			case SDL_SCANCODE_LEFT:
			case SDL_SCANCODE_A:
				MM.sideChange(2, &AU_Snake_left, UM.CheckPause());
				break;

			case SDL_SCANCODE_RIGHT:
			case SDL_SCANCODE_D:
				MM.sideChange(3, &AU_Snake_right, UM.CheckPause());
				break;

			case SDL_SCANCODE_DOWN:
			case SDL_SCANCODE_S:
				MM.sideChange(4, &AU_Snake_down, UM.CheckPause());
				break;
			case SDL_SCANCODE_ESCAPE:
				UM.sendMessage("ESC");
				break;
			case SDL_SCANCODE_SPACE:
				UM.sendMessage("SPACE");
				break;
		}
		break;

	default:
		break;
	}
}
void GameMain::Render()
{
	if (SDL_GetTicks() > oldTime + (1000.0 / FPS))
	{
		// Render copy function
		TM_BackGround.RenderTexture(gameRender, 0, 0, gameWindowWidth, gameWindowHeight);
		TM_Board.RenderTexture(gameRender, 50, 150, 700, 700);
		AO_Aplle.RApple(gameRender, TM_Apple.ReturnTexture(), MM.YXposNUM,MM.length);
		AO_Aplle.RAte(gameRender, TM_Eat_Animation.ReturnTexture());
		SR.RSnake(gameRender,TM_SnakeHead.ReturnTexture(),TM_Dot.ReturnTexture(),TM_SnakeBody.ReturnTexture(),TM_SnakeEyes.ReturnTexture(),TM_SnakeEye.ReturnTexture(), TM_SnakeMoutch.ReturnTexture(),MM.YXposNUM,MM.length,UM.CheckPause()); 
		MM.renderCrash(gameRender, TM_SnakeHit.ReturnTexture(), &AU_Snake_crash);
		UM.RStat(gameRender, TM_Apple.ReturnTexture(), TM_Cup.ReturnTexture(), MM.length);

		UM.RGui(gameRender,&UMB_Play, &UMB_Settings, &UMB_Back,&UMBa_Volume,&UMBa_Speed,TM_Volume.ReturnTexture(),TM_Speed.ReturnTexture());
		UMB_Close.renderButton(gameRender, 255);
		if (UMB_SoundOn.isActive() == true)
		{
			UMB_SoundOn.renderButton(gameRender, 255);
			AU_Button.setIsOff(false);
			AU_Snake_up.setIsOff(false);
			AU_Snake_down.setIsOff(false);
			AU_Snake_left.setIsOff(false);
			AU_Snake_right.setIsOff(false);
			AU_Snake_ate.setIsOff(false);
			AU_Snake_crash.setIsOff(false);
		};
		if (UMB_SoundOff.isActive() == true)
		{
			UMB_SoundOff.renderButton(gameRender, 255);
			AU_Button.setIsOff(true);
			AU_Snake_up.setIsOff(true);
			AU_Snake_down.setIsOff(true);
			AU_Snake_left.setIsOff(true);
			AU_Snake_right.setIsOff(true);
			AU_Snake_ate.setIsOff(true);
			AU_Snake_crash.setIsOff(true);
		};
		UM.Start(gameRender, TM_Start.ReturnTexture());

		SDL_RenderSetScale(gameRender, sizeMultiplier, sizeMultiplier);
		SDL_RenderPresent(gameRender);

		// Set old time to present
		oldTime = SDL_GetTicks();
	};
}

void GameMain::RenderClear()
{
	SDL_RenderClear(gameRender);
}

bool GameMain::RunReturn()
{
	return run;
}