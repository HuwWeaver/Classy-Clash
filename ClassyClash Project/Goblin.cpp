#include "Goblin.h"

Goblin::Goblin(Vector2 pos)
{
    worldPos = pos;
    idle = LoadTexture("characters/goblin_idle_spritesheet.png");
    run =  LoadTexture("characters/goblin_run_spritesheet.png");
    texture = idle;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 4.0f;
}