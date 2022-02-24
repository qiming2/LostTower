#include "Renderer.h"
#include "Util.h"
#include "AssetPool.h"
#include "Camera.h"
#include "GameObject.h"
#include "Input/KeyListener.h"

Renderer* Renderer::getInstance()
{
	static Renderer* instance = new Renderer();
	return instance;
}

void Renderer::render()
{
	
	glBindVertexArray(vao);
	sprite_shader->bind();
	sprite_shader->set4fv("projection", Camera::getInstance()->getOrthoProjectionMatrix());
	sprite_shader->set4fv("view", Camera::getInstance()->getView());
	
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

void Renderer::renderSpriteSheet()
{

	// Working animation and need to clean it up
	// Experiment with rebuffer data and do a animation
	static bool runAnime = false;
	static int count = 0;
	static float secondPerF = 1.0f / 15.0f;
	static float timer = secondPerF + 0.1f;
	static float offset = 48.0f / 288.0f;
	//only switch to another spirte
	//when hitting secondPerF time
	if (KeyListener::isKeyPressed(GLFW_KEY_SPACE)) {
		runAnime = true;
	}

	std::vector<glm::vec2> uvs;
	if (runAnime) {
		timer += Window::getFrameRate();
		if (timer >= secondPerF) {
			
			timer = 0.0f;
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			uvs.push_back({ offset * count, 1.0f });
			uvs.push_back({ offset * count, 0.0f });
			uvs.push_back({ offset * count + offset, 0.0f });
			uvs.push_back({ offset * count, 1.0f });
			uvs.push_back({ offset * count + offset, 0.0f });
			uvs.push_back({ offset * count + offset, 1.0f });
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 2, sizeof(float) * 2, &uvs[0]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 6, sizeof(float) * 2, &uvs[1]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 10, sizeof(float) * 2, &uvs[2]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 14, sizeof(float) * 2, &uvs[3]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 18, sizeof(float) * 2, &uvs[4]);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 22, sizeof(float) * 2, &uvs[5]);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			count++;
			if (count == 6) {
				count = 0;
				runAnime = false;
			}
		}
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		uvs.push_back({ 0.0f, 1.0f });
		uvs.push_back({ 0.0f, 0.0f });
		uvs.push_back({ 0.0f + offset, 0.0f });
		uvs.push_back({ 0.0f, 1.0f });
		uvs.push_back({ 0.0f + offset, 0.0f });
		uvs.push_back({ 0.0f + offset, 1.0f });
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 2, sizeof(float) * 2, &uvs[0]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 6, sizeof(float) * 2, &uvs[1]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 10, sizeof(float) * 2, &uvs[2]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 14, sizeof(float) * 2, &uvs[3]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 18, sizeof(float) * 2, &uvs[4]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 22, sizeof(float) * 2, &uvs[5]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	

	// Normal code
	glBindVertexArray(vao);
	sprite_shader->bind();
	sprite_shader->set4fv("projection", Camera::getInstance()->getOrthoProjectionMatrix());
	sprite_shader->set4fv("view", Camera::getInstance()->getView());
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

	// send texture unit ids once
	static std::vector<int> tius = { 0, 1, 2, 3, 4, 5, 6, 7 };
	sprite_shader->bind();
	sprite_shader->setiArray("tex", tius.size(), &tius.data()[0]);
}
