#include "CollisionManager.h"

CollisionManager* CollisionManager::getInstance()
{
    static CollisionManager* _instance = new CollisionManager();
    return _instance;
}

void CollisionManager::update(float dt)
{
    // Collision detection and resolution

}

CollisionManager::~CollisionManager()
{
}
