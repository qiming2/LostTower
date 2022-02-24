#pragma once
#include "Component/Collider2D.h"
#include <vector>

// Detect collision and resolve collision detection if necessary
class CollisionManager
{
public:
	static CollisionManager* getInstance();
	void update(float dt);
	~CollisionManager();
private:
	std::vector<Collider2D> colliders;
};

