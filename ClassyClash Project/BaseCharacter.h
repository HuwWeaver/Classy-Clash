#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement(float axis);
    Rectangle getCollisionRect();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() {return alive;};
    void setAlive(bool isAlive) {alive = isAlive;};

protected:
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Texture2D texture{idle};
    Vector2 worldPos{}, worldPosLastFrame{};
    // Anim Variables
    float rightLeft{1.0f}; // 1=Facing Right, -1=Facing Left
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.0f / 12.0f};
    float speed{5.0f};
    float width{}, height{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif