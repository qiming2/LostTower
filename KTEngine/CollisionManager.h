#pragma once
#include "Component/Collider2D.h"
#include <vector>

// Detect collision and resolve collision detection if necessary
class CollisionManager
{
public:
	static CollisionManager* getInstance();
	void addCollider2D(Ref<Collider2D>);
	void update(float dt);
	~CollisionManager();
private:
	CollisionManager();
	std::vector<Ref<Collider2D>> m_colliders;
};

