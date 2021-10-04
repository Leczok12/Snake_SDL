#pragma once
#include <SDL_mixer.h>

class AudioMenager
{
private:
	Mix_Chunk* sound;
	bool isOff;
	int volume;
public:
	AudioMenager()
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		isOff = false;
		volume = 128;
		for (int i = 0; i < 8; i++)
		{
			sound = nullptr;
		};
	};

	~AudioMenager()
	{
		Mix_CloseAudio();
	};

	void load(const char* src)
	{
		sound = Mix_LoadWAV(src);
	};

	void play()
	{
		setVolume();
		Mix_PlayChannel(-1 ,sound, 0);
	};

	void setVolume()
	{
		if (isOff == true)
		{
			Mix_Volume(-1, 0);
		}
		else
		{
			Mix_Volume(-1, volume);
		};
	};

	void changeVolume(int v)
	{
		volume = v;
	};

	void setIsOff(bool set)
	{
		isOff = set;
	};
};