#include "Game.h"

namespace Engine
{
    std::unique_ptr<Player> player;
    std::unique_ptr<Bullet> bullet;
    std::vector<Enemy> enemies;
    std::unique_ptr<Entity> background;

    GameScreen currentScreen = TITLE;
    int score = 0;
    float spawnTimer = 0;
    float backgroundSpeed = 115;
    Sound clickSound;

    void StartGame(int width, int height, const char* title)
    {
        SetRandomSeed(time(0));

        InitWindow(width, height, title);
        SetWindowState(FLAG_VSYNC_HINT);

        InitAudioDevice();

        clickSound = LoadSound("res/sound/click.wav");

        player = std::make_unique<Player>(400, 415);
        bullet = std::make_unique<Bullet>(-100, 415);
        background = std::make_unique<Entity>(400, 300, "res/img/background.png");
    }

    void RunGame()
    {
        while (!WindowShouldClose())
        {
            UpdateLoop();

            BeginDrawing();

                DrawLoop();

            EndDrawing();
        }
    }

    void UpdateLoop()
    {
        if (currentScreen == TITLE)
        {
            if (IsMouseButtonPressed(0))
            {
                PlaySound(clickSound);
                currentScreen = GAMEPLAY;
            }
        }
        else if (currentScreen == GAMEPLAY)
        {
            player->Update(bullet);

            bullet->Update();

            for (uint32_t j = 0; j < enemies.size(); j++)
            {
                enemies[j].Update(player->GetPosition());
                if (CheckCollisionRecs(bullet->GetCollider(), enemies[j].GetCollider()))
                {
                    score += 100;
                    enemies.erase(enemies.begin() + j);
                    bullet->Destroy();
                }

                if (CheckCollisionRecs(player->GetCollider(), enemies[j].GetCollider()))
                {
                    player->Damage();
                }
            }

            if (player->GetHealth() <= 0)
            {
                enemies.clear();
                player->ResetHealth();
                bullet->Destroy();
                score = 0;
                currentScreen = TITLE;
            }

            SpawnEnemies();

            if (score < 10000)
                backgroundSpeed = 115;
            else
                backgroundSpeed = 170;
            background->ParallaxX(backgroundSpeed);
        }
    }

    void SpawnEnemies()
    {
        spawnTimer += GetFrameTime();

        if (spawnTimer > 1.3)
        {
            int side = GetRandomValue(1, 2);

            switch (side)
            {
            case 1:
                enemies.push_back(Enemy(GetRandomValue(0, 800), -50));
                if (score >= 10000)
                    enemies.push_back(Enemy(GetRandomValue(0, 800), 650));
                break;
            default:
                int sideX = GetRandomValue(1, 2);
                if (sideX == 1)
                {
                    enemies.push_back(Enemy(-50, GetRandomValue(0, 600)));
                    if (score >= 10000)
                        enemies.push_back(Enemy(850, GetRandomValue(0, 600)));
                }
                else
                {
                    enemies.push_back(Enemy(850, GetRandomValue(0, 600)));
                    if (score >= 10000)
                        enemies.push_back(Enemy(-50, GetRandomValue(0, 600)));
                }
                break;
            }
            
            spawnTimer = 0;
        }
    }

    void DrawLoop()
    {
        ClearBackground(BLACK);

        if (currentScreen == TITLE)
        {
            background->Render();
            player->Render();
            player->cannon->Render();

            DrawText("Space Runner", 225, 90, 50, WHITE);

            DrawText("Tap or Click to Play!", 235, 465, 30, WHITE);
        }
        else if (currentScreen == GAMEPLAY)
        {
            background->Render();
            player->Render();
            player->cannon->Render();

            for (Enemy& enemy : enemies)
            {
                enemy.Render();
            }

            bullet->Render();

            DrawRectangle(15, 55, 200, 20, BLACK);
            DrawRectangle(15, 55, player->GetHealth() * 20, 20, GREEN);

            std::string scoreText = "Score: " + std::to_string(score);
            DrawText(scoreText.c_str(), 15, 15, 30, WHITE);
        }
    }

    void CloseGame()
    {
        CloseAudioDevice();
        CloseWindow();
    }
}