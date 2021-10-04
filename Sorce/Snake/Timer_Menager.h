#pragma once
#include <SDL.h>
#include <sstream>

using namespace std;

class Timer_Menager
{
public:
	Timer_Menager()
	{
		ms = 0;
		s = 0; 
		m = 0; 
		h = 0;
		startTime = 0;
		isCounting = false;
	}
	~Timer_Menager()
	{

	}
	void start()
	{
		startTime = SDL_GetTicks();
		isCounting = true;
	}
	void stop()
	{
		isCounting = false;
	}
	const char * returnClock()
	{
		if (isCounting == true)
		{
			//std::cout << ((SDL_GetTicks() - startTime) / 10) % 100 << " | " << ((SDL_GetTicks() - startTime) / 1000) % 60 << " | " << ((SDL_GetTicks() - startTime) / 60000) % 60 << " | " << ((SDL_GetTicks() - startTime) / 6000000) % 60 << std::endl;
			ms = ((SDL_GetTicks() - startTime) / 100) % 10;
			s = ((SDL_GetTicks() - startTime) / 1000) % 60;
			m = ((SDL_GetTicks() - startTime) / 60000) % 60;
			h = ((SDL_GetTicks() - startTime) / 6000000) % 60;
			stringstream msToString("");
			stringstream sToString("");
			stringstream mToString("");
			stringstream hToString("");

			msToString << ":" << ms;

			if (s < 10)
			{
				sToString << ":0" << s;
			}
			else
			{
				sToString << ":" << s;
			};

			if (m < 10)
			{
				mToString << ":0" << m;
			}
			else
			{
				mToString << ":" << m;
			};

			if (h < 10)
			{
				hToString << "0" << h;
			}
			else
			{
				hToString << h;
			};

			stringstream toConvert("");
			toConvert << hToString.str().c_str();
			toConvert << mToString.str().c_str();
			toConvert << sToString.str().c_str();
			toConvert << msToString.str().c_str();
			return to_cstr(std::move(toConvert).str());
		}
		else
		{
			stringstream msToString("");
			stringstream sToString("");
			stringstream mToString("");
			stringstream hToString("");

			msToString << ":" << ms;

			if (s < 10)
			{
				sToString << ":0" << s;
			}
			else
			{
				sToString << ":" << s;
			};

			if (m < 10)
			{
				mToString << ":0" << m;
			}
			else
			{
				mToString << ":" << m;
			};

			if (h < 10)
			{
				hToString << "0" << h;
			}
			else
			{
				hToString << h;
			};

			stringstream toConvert("");
			toConvert << hToString.str().c_str();
			toConvert << mToString.str().c_str();
			toConvert << sToString.str().c_str();
			toConvert << msToString.str().c_str();
			return to_cstr(std::move(toConvert).str());
		};
	}
	const char* to_cstr(string&& s)
	{
		static thread_local string sloc;
		sloc = move(s);
		return sloc.c_str();
	}
private:
	int ms, s, m, h;
	Uint32 startTime;
	bool isCounting;
};
