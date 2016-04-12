#include <iostream>
#include <Windows.h>
#include "Game.h"
void main()
{
	Game* game = new Game();
	game->Initialize();

	//std::cout << "dd";

	while (true)
	{
 		game->Update();
		game->Render();
	}
	SAFE_DELETE(game);

	system("pause");
	return;
}