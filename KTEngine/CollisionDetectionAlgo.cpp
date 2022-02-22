#include "CollisionDetectionAlgo.h"
#include "Util/k_print.h"

namespace col_algo {
	collider_resolution checkCollision(Collider2D* a, Collider2D* b) {
		switch (a->m_type) {
		case ColliderType::Circle:
			
			break;
		case ColliderType::Polygon:
			break;
		default:
			ekp(a->m_type, " can not be handled");
		
		}
	}

	// Circle vs Circle
	collider_resolution checkCollision(CircleCollider* a, CircleCollider* b)
	{
		collider_resolution ret;
		
	}
}