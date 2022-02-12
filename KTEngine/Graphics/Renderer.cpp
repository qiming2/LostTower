#include "Renderer.h"
#include "Util.h"
#include "AssetPool.h"
#include "Camera.h"
#include "GameObject.h"

Renderer* Renderer::getInstance()
{
	static Renderer* instance = new Renderer();
	return instance;
}

void Renderer::render()
{
	static std::vector<int> tius = { 0, 1, 2, 3, 4, 5, 6, 7 };
	glBindVertexArray(vao);
	sprite_shader->bind();
	sprite_shader->set4fv("projection", Camera::getInstance()->getOrthoProjectionMatrix());
	sprite_shader->set4fv("view", Camera::getInstance()->getView());
	sprite_shader->setiArray("tex", tius.size(), &tius.data()[0]);
	glm::mat4 model;
	for (Ref<SpriteRenderer> sp : sprnds) {
		sp->getTexture()->bind();
		sprite_shader->seti("texId", sp->getTexture()->getID());
		sp->gameObject->transform.fillModelMatrix(model);
		sprite_shader->set4fv("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	sprite_shader->unBind();
	glBindVertexArray(0);
}

void Renderer::addSpriteRenderer(Ref<SpriteRenderer> spr)
{
	sprnds.push_back(spr);
}

Renderer::Renderer()
{
	std::vector<float> vertices = Util::spriteQuad();
	// vao, vbo set up
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), (void*)vertices.data(), GL_STATIC_DRAW));

	// vertex attribute

	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2)));
	GLCall(glEnableVertexAttribArray(1));
	glBindVertexArray(0);

	sprite_shader = AssetPool::getShader("KTEngine/Asset/Shader/default.glsl");
	
}
