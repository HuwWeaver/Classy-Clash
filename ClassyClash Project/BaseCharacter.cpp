#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::undoMovement(float axis)
{
    if (axis == -1.0f) // X axis
    {
        worldPos.x = worldPosLastFrame.x;
    }
    else if (axis == 0.0f) // Both axis
    {
        worldPos = worldPosLastFrame;
    }
    else if (axis == 1.0f) // Y axis
    {
        worldPos.y = worldPosLastFrame.y;
    }
}

Rectangle BaseCharacter::getCollisionRect()
{
    return Rectangle{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // Update character animation
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // Set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // Draw Character
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}