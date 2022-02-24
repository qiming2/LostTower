#include "Collider2D.h"
#include "Util/k_print.h"

IMP_COMPONENT_TYPE(Collider2D);

std::ostream& operator<<(std::ostream& stream, ColliderType type) {
	switch (type) {
	case ColliderType::None:
		stream << "None Collider";
		break;
	case ColliderType::Circle:
		stream << "Circle Collider";
		break;
	case ColliderType::Polygon:
		stream << "Polygon Collider";
		break;
	default:
		stream << "Unknown type Collider";
	}
	return stream;
}


Collider2D::Collider2D(ColliderType type)
{
	this->m_type = type;
}

Collider2D::~Collider2D()
{
}

collider_resolution::collider_resolution()
	: length(0.0f),
	slide_vec(0.0f),
	isCollided(false)
{
}

PolygonCollider::PolygonCollider()
	:Collider2D(ColliderType::Polygon)
{
}


CircleCollider::CircleCollider()
	:Collider2D(ColliderType::Circle)
{
}
