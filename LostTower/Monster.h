#pragma once
#include "GameObject.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Input/KeyListener.h"
#include "Animation.h"


class Monster : public GameObject
{
public:
	Monster();
	~Monster();
	void update(float dt);
	void imgui();
	void onTrigger(Collider2D*) override;
private:
	glm::mat4 model;
	Camera* camera;
	float speed;
};

