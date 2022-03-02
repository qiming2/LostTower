#include <limits>
#include "CollisionDetectionAlgo.h"
#include "Util/k_print.h"

namespace k_col_algo {
	collider_resolution checkCollision(Collider2D* a, Collider2D* b) {
		collider_resolution ret;
		if (a->m_type == ColliderType::Circle) {
			if (b->m_type == ColliderType::Circle) {
				ret = checkCollision((CircleCollider*)a, (CircleCollider*)b);
			}
			else if (b->m_type == ColliderType::Polygon){
				ekp("Not implemented");
			}
			else {
				ekp("UNKNOWN TYPE B: ", b->m_type);
			}
		}
		else if (a->m_type == ColliderType::Polygon) {

			if (b->m_type == ColliderType::Circle) {
				ekp("Not implemented");
			} else if (b->m_type == ColliderType::Polygon) {
				ret = checkCollision((PolygonCollider*)a, (PolygonCollider*)b);
			} else {
				ekp("UNKNOWN TYPE B: ", b->m_type);
			}
		}
		else {
			ekp("UKNOWN TYPE A: ", a->m_type);
		}
		return ret;
	}

	// Circle vs Circle
	collider_resolution checkCollision(CircleCollider* a, CircleCollider* b)
	{
		collider_resolution ret = collider_resolution();
		glm::vec3 disVec = a->origin - b->origin;
		float cToCDistSquare = disVec[0] * disVec[0] + disVec[1] * disVec[1] + disVec[2] * disVec[2];
		float radiusSumSquare = (a->radius + b->radius) * (a->radius + b->radius);
		// Collided
		if (cToCDistSquare < radiusSumSquare) {
			ret.isCollided = true;
			ret.length = sqrtf(radiusSumSquare) - sqrtf(cToCDistSquare);
			ret.slide_vec = glm::normalize(disVec);
		}
		return ret;
	}


	// Polygon vs Polygon SAT test and resolution
	// Complete!!
	collider_resolution checkCollision(PolygonCollider* a, PolygonCollider* b)
	{
		collider_resolution ret = collider_resolution();
		// SAT theorem
		// Check b's points against a's normals
		const std::vector<glm::vec3>& apoints = a->points;
		size_t asize = apoints.size();
		const std::vector<glm::vec3>& bpoints = b->points;
		size_t bsize = bpoints.size();
		glm::vec3 normal = glm::vec3(0.0f);
		glm::vec3 cur_edge = glm::vec3(0.0f);
		glm::vec3 cur_point(1.0f);
		
		float amin = std::numeric_limits<float>::max();
		float bmin = std::numeric_limits<float>::max();
		float amax = -std::numeric_limits<float>::max();
		float bmax = -std::numeric_limits<float>::max();

		glm::vec3 temp_edge(1.0f);
		float dotVal = 0.0f;

		float minDisplace = std::numeric_limits<float>::max();
		float localMinDis = 0.0f;
		for (size_t i = 0; i < apoints.size(); ++i) {
			amin = std::numeric_limits<float>::max();
			bmin = std::numeric_limits<float>::max();
			amax = -std::numeric_limits<float>::max();
			bmax = -std::numeric_limits<float>::max();
			cur_point = apoints[i];
			cur_edge = apoints[(i + 1) % asize] - cur_point;
			// points are ordered counterclockwise
			// thus we need to compute the right 
			// normal which is <dy, -dx, 0>
			normal = glm::normalize(glm::vec3(cur_edge[1], -cur_edge[0], 0.0f));
			for (const glm::vec3& p : apoints) {
				temp_edge = p - cur_point;
				dotVal = glm::dot(temp_edge, normal);
				if (amin > dotVal) {
					amin = dotVal;
				}

				if (amax < dotVal) {
					amax = dotVal;
				}
			}

			for (const glm::vec3& p : bpoints) {
				temp_edge = p - cur_point;
				dotVal = glm::dot(temp_edge, normal);
				if (bmin > dotVal) {
					bmin = dotVal;
				}

				if (bmax < dotVal) {
					bmax = dotVal;
				}
			}

			// If there is any axis check that
			// results in no collision, we can
			// safely conclude that these two
			// polygons are not colliding
			if (amax < bmin || bmax < amin) {
				return ret;
			}

			// record the distance
			localMinDis = amax - bmin < bmax - amin ? amax - bmin : bmax - amin;
			normal = localMinDis * normal;
			localMinDis = normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2];

			if (localMinDis < minDisplace) {
				minDisplace = localMinDis;
				ret.slide_vec = normal;
			}
		}

		// Do the same for b
		for (size_t i = 0; i < bpoints.size(); ++i) {
			amin = std::numeric_limits<float>::max();
			bmin = std::numeric_limits<float>::max();
			amax = -std::numeric_limits<float>::max();
			bmax = -std::numeric_limits<float>::max();
			cur_point = bpoints[i];
			cur_edge = bpoints[(i + 1) % bsize] - cur_point;
			// points are ordered counterclockwise
			// thus we need to compute the right 
			// normal which is <dy, -dx, 0>
			normal = glm::normalize(glm::vec3(cur_edge[1], -cur_edge[0], 0.0f));
			for (const glm::vec3& p : apoints) {
				temp_edge = p - cur_point;
				dotVal = glm::dot(temp_edge, normal);
				if (amin > dotVal) {
					amin = dotVal;
				}

				if (amax < dotVal) {
					amax = dotVal;
				}
			}

			for (const glm::vec3& p : bpoints) {
				temp_edge = p - cur_point;
				dotVal = glm::dot(temp_edge, normal);
				if (bmin > dotVal) {
					bmin = dotVal;
				}

				if (bmax < dotVal) {
					bmax = dotVal;
				}
			}

			// If there is any axis check that
			// results in no collision, we can
			// safely conclude that these two
			// polygons are not colliding
			if (amax < bmin || bmax < amin) {
				return ret;
			}

			// record the distance
			localMinDis = amax - bmin < bmax - amin ? amax - bmin : bmax - amin;
			normal = localMinDis * normal;
			localMinDis = normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2];

			// Since we want to check collision
			// in terms of a, we need to flip
			// normal sign in order to resolve a's
			// position
			if (localMinDis < minDisplace) {
				minDisplace = localMinDis;
				ret.slide_vec = -normal;
			}
		}

		// we normalize direction and get length of it
		ret.length = glm::length(ret.slide_vec);
		ret.slide_vec = glm::normalize(ret.slide_vec);
		ret.isCollided = true;
		if (ret.isCollided) {
			kp("Length, slide_vec: ", ret.length, " ", ret.slide_vec);
		}
		return ret;
	}
}
