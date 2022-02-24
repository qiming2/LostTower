#pragma once
#include "GameObject.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Input/KeyListener.h"
#include "Player.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void update(float dt);
	void imgui();
private:
	glm::mat4 model;
	Camera* camera;
	float speed;
};

