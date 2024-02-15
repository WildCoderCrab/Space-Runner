#include "Game.h"

int main()
{
    Engine::StartGame(800, 600, "Space Runner");

    Engine::RunGame();

    Engine::CloseGame();
    
    return 0;
}