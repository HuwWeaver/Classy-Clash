#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include "Goblin.h"
#include "Slime.h"

int main()
{
    // Window Dimensions
    int windowDimensions[2];
    windowDimensions[0] = 1024;
    windowDimensions[1] = 768;

    InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");

    // Background image
    Texture2D map = LoadTexture("textures/OpenWorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowDimensions[0], windowDimensions[1]};

    Prop props[2]{
        Prop{LoadTexture("nature_tileset/Rock.png"), Vector2{600.0f, 300.0f}},
        Prop{LoadTexture("nature_tileset/Log.png"), Vector2{400.0f, 500.0f}}};

    
    Goblin goblin{Vector2{700.0f, 500.0f}};

    Slime slime{Vector2{500.0f, 700.0f}};
    
    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Delta time
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        // Draw Map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        // Draw Props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive()) // Character not alive
        {
            DrawText("Game Over!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.0f, 45.0f, 40, RED);
        }

        knight.tick(dt);

        // Check map bounds
        if (knight.getWorldPos().x + 325.0f < 0.0f || knight.getWorldPos().x + windowDimensions[0] - 325.0f > map.width * mapScale)
        {
            if (knight.getWorldPos().y + 220.0f < 0.0f || knight.getWorldPos().y + windowDimensions[1] - 220.0f > map.height * mapScale)
            {
                knight.undoMovement(0.0f); // Hit both x and y axis block
            }

            knight.undoMovement(-1.0f); // hit just x axis block
        }
        else if (knight.getWorldPos().y + 220.0f < 0.0f || knight.getWorldPos().y + windowDimensions[1] - 220.0f > map.height * mapScale)
        {
            knight.undoMovement(1.0f); // hit just y axis block
        }

        // check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRect(knight.getWorldPos()), knight.getCollisionRect()))
            {
                knight.undoMovement(0.0f);
                break;
            }
        }

        // tick all enemies
        for (auto enemy : enemies)
        {
            enemy->tick(dt);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRect(), knight.getWeaponCollisionRect()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    // Unload all textures
    UnloadTexture(map);

    CloseWindow();
}