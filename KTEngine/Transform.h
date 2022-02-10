#pragma once
#include "GLM/glm.hpp"
#include <GLM/ext/matrix_transform.hpp>
class Transform
{
public:
	Transform();
	~Transform();
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	void move(glm::vec3 direction, float speed);
	void rotate(glm::vec3 rotation);
	void changeScale(glm::vec3 scaleV);
	void fillModelMatrix(glm::mat4& model);
};

