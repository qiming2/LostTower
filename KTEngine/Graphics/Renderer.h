#pragma once
#include <memory>
#include <vector>
#include "SpriteRenderer.h"
#include "Shader.h"

class Renderer
{
public:
	static Renderer* getInstance();
	void render();

	// Temporary!!!!!!!!!
	void renderSpriteSheet();


	void addSpriteRenderer(Ref<SpriteRenderer> spr);
private:
	Renderer();
	unsigned int vao, vbo;
	// Hold a list of SpriteRenderer
	std::vector<Ref<SpriteRenderer>> sprnds;
	Ref<Shader> sprite_shader;
};

