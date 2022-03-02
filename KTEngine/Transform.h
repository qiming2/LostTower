#pragma once
#include "GLM/glm.hpp"
#include <GLM/ext/matrix_transform.hpp>

// Transform class is not at all efficient and performent
// it is a way for me to get familiar with matrix and vec operations

class Transform
{
public:
	Transform();
	~Transform();
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	void move(glm::vec3 direction, float speed);
	void move(glm::vec3 vec);
	void rotate(glm::vec3 rotation);
	void changeScale(glm::vec3 scaleV);
	void fillModelMatrix(glm::mat4& model);
};

