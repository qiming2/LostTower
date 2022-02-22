#include "Transform.h"

Transform::Transform()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Transform::move(glm::vec3 direction, float speed) {
	position = glm::translate(glm::mat4(1.0f), normalize(direction) * speed) * glm::vec4(position, 1.0f);
}

void Transform::rotate(glm::vec3 rotation) {
	this->rotation += rotation;
}

void Transform::changeScale(glm::vec3 scaleV)
{
	scale = scaleV;
	scale[2] = 1.0f;
}

void Transform::fillModelMatrix(glm::mat4& model)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position));
	model = glm::rotate(model, rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);
}

Transform::~Transform()
{
}
