#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy();
    virtual void tick(float deltaTime) override;
    void setTarget(Character* newTarget) {target = newTarget;};
    virtual Vector2 getScreenPos() override;

protected:
    Character* target;
    float damagePerSec{10.0f};
    float maxRadius{250.0f}, minRadius{25.0f};

};

#endif