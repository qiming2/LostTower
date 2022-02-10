#pragma once
#include "GameObject.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Input/KeyListener.h"

class Monster : public GameObject
{
public:
	Monster();
	~Monster();
	void update(float dt);
	void imgui();
private:
	Ref<Shader> shader;
	Ref<Texture> tex;
	unsigned int vao, vbo;
	glm::mat4 model;
	Camera* camera;
	float speed;
};

