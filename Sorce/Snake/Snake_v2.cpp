#include <SDL.h>
#include "GameMain.h"

GameMain GM = GameMain("Snake", 800, 900);

int main(int argc,char* args[])
{
    while (GM.RunReturn() == true)
    {
        GM.RenderClear();
        GM.MsgLoop();
        GM.Render();
    };
	return 0;
}