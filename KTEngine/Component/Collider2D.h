#pragma once
#include <ostream>
#include "GLM/glm.hpp"
#include "Component/Component.h"




enum class ColliderType {
	None = 0,
	Circle,
	Polygon
};

std::ostream& operator<<(std::ostream& stream, ColliderType type);

struct collider_resolution {
	glm::vec3 slide_vec;
	float length;
	bool isCollided;
	collider_resolution();
};

struct Collider2D : public Component
{
	COMPONENT_TYPE(Collider2D);
public:
	Collider2D(ColliderType type);
	~Collider2D();
	ColliderType m_type;
};

struct CircleCollider : public Collider2D {
	CircleCollider();
	glm::vec3 origin;
	float radius;
};

struct PolygonCollider : public Collider2D {
	// Always order the vertices counterclock-wise
	PolygonCollider();
	std::vector<glm::vec3> points;
};