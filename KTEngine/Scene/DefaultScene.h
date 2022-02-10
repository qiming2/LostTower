#pragma once
#include "Scene.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Player.h"
#include "Monster.h"

class DefaultScene : public Scene
{
public:
	DefaultScene();
	DefaultScene(const std::string& name);
	~DefaultScene();
	virtual void update(float dt) override;
	virtual void imgui() override;

private:
	
	Ref<Shader> background_shader;
	Ref<Texture> background_tex;
	
	unsigned int vao, vbo;
	glm::mat4 model;
	Camera* camera;
	Player player;
	Monster monster;
};

