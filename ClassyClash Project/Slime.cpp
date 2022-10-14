#include "Slime.h"

Slime::Slime(Vector2 pos)
{
    worldPos = pos;
    idle = LoadTexture("characters/slime_idle_spritesheet.png");
    run = LoadTexture("characters/slime_run_spritesheet.png");
    texture = idle;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 4.0f;
}