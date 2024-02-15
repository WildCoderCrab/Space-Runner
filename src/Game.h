#pragma once

#include <raylib.h>
#include <memory>
#include <vector>
#include <iostream>
#include <time.h>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

namespace Engine
{
    typedef enum GameScreen
    {
        TITLE = 0,
        GAMEPLAY
    } GameScreen;

    void StartGame(int width, int height, const char* title);

    void RunGame();

    void UpdateLoop();
    void SpawnEnemies();

    void DrawLoop();

    void CloseGame();
}