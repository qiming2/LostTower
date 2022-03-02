#include "Collider2D.h"
#include "Util/k_print.h"
#include "CollisionManager.h"

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


Collider2D::Collider2D(ColliderType type) :
	Component()
{
	this->m_type = type;
}

Ref<Collider2D> Collider2D::createCollider2D(ColliderType type)
{
	Collider2D* ptr = nullptr;
	switch (type) {
	case ColliderType::Circle:
		ptr = new CircleCollider();
		break;
	case ColliderType::Polygon:
		ptr = new PolygonCollider();
		break;
	default:
		ekp("UNKNOWN TYPE: ", type);
	}
	// Add it to the collision manager
	Ref<Collider2D> ret = Ref<Collider2D>(ptr);
	CollisionManager::getInstance()->addCollider2D(ret);
	return ret;
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
	// a box polygon collider with 1/1 width/height
	points.push_back(glm::vec3(0.5f, 0.5f, 0.0f));
	points.push_back(glm::vec3(-0.5f, 0.5f, 0.0f));
	points.push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
	points.push_back(glm::vec3(0.5f, -0.5f, 0.0f));
}


CircleCollider::CircleCollider()
	:Collider2D(ColliderType::Circle)
{
	// default config
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
	radius = 0.5f;
}
