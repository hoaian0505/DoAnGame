#include <windows.h>
#include <stdlib.h>

#include "MainGame.h"



	
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		srand(time(NULL));
		MainGame thisGame(hInstance, "Castlevania", 0, 80);
		thisGame.Init();
		thisGame.Run();
		return 0;
	}