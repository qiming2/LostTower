#pragma once
#include "Component/Collider2D.h"

namespace col_algo {
	collider_resolution checkCollision(Collider2D*, Collider2D*);
	collider_resolution checkCollision(CircleCollider*, CircleCollider*);
	collider_resolution checkCollision(PolygonCollider*, PolygonCollider*);
}

