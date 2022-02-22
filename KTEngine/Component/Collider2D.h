#pragma once
#include "GLM/glm.hpp"
#include "Component/Component.h"

enum class ColliderType {
	None = 0,
	Circle,
	Polygon
};

struct collider_resolution {
	glm::vec3 slide_vec;
	float length;
	bool isCollided;
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
	float origin;
	float radius;
};

struct PolygonCollider : public Collider2D {
	// Always order the vertices counterclock-wise 
	std::vector<glm::vec3> points;
};