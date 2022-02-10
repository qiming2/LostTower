#pragma once
#include "Common.h"
#include "GLM/glm.hpp"
#include <GLM/ext/matrix_transform.hpp>
#include <GLM/ext/matrix_clip_space.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void update(float dt);
	glm::mat4 getOrthoProjectionMatrix();
	glm::mat4 getView();
	static Camera* getInstance();
private:
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec3 position;
	glm::mat4 model;
	glm::vec3 direction;
};

