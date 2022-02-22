#include "Collider2D.h"
#include "Util/k_print.h"

IMP_COMPONENT_TYPE(Collider2D);

Collider2D::Collider2D(ColliderType type)
{
	this->m_type = type;
}

Collider2D::~Collider2D()
{
}

