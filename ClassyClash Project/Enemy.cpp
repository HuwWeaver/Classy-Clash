#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy()
{
}

void Enemy::tick(float deltaTime)
{
    if(!getAlive()) return;
    
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < minRadius || Vector2Length(velocity) > maxRadius) velocity = {};
    BaseCharacter::tick(deltaTime);

    if(CheckCollisionRecs(target->getCollisionRect(), getCollisionRect()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
