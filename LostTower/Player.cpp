#include "Player.h"
#include "Util/Util.h"
#include "AssetPool.h"
#include <vector>

Player::Player() :
	GameObject()
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
	shader = AssetPool::getShader("KTEngine/Asset/Shader/default.glsl");
	shader->bind();
	unsigned int id = 0;
	shader->seti("tex", id);
	model = glm::mat4(1.0f);
	tex = AssetPool::getTexture("LostTower\\Asset\\se_1.jpg", id);
	camera = Camera::getInstance();

	speed = 10.0f;
	tag = "Da Sha Bi";
}

Player::~Player()
{
}

void Player::update(float dt)
{
	if (KeyListener::isKeyPressed(GLFW_KEY_W) || KeyListener::isKeyPressed(GLFW_KEY_UP)) {
		transform.move(glm::vec3(0.0f, 1.0f, 0.0f), speed);

	}
	else if (KeyListener::isKeyPressed(GLFW_KEY_S) || KeyListener::isKeyPressed(GLFW_KEY_DOWN)) {
		transform.move(glm::vec3(0.0f, -1.0f, 0.0f), speed);
	}
	else if (KeyListener::isKeyPressed(GLFW_KEY_A) || KeyListener::isKeyPressed(GLFW_KEY_LEFT)) {
		transform.move(glm::vec3(-1.0f, 0.0f, 0.0f), speed);
	}
	else if (KeyListener::isKeyPressed(GLFW_KEY_D) || KeyListener::isKeyPressed(GLFW_KEY_RIGHT)) {
		transform.move(glm::vec3(1.0f, 0.0f, 0.0f), speed);
	}
	
	transform.changeScale(glm::vec3(100.0f, 100.0f, 100.0f));
	transform.rotate(glm::vec3(0.0f, 0.0f, dt));
	transform.fillModelMatrix(model);


	GLCall(glBindVertexArray(vao));
	shader->bind();
	shader->set4fv("projection", camera->getOrthoProjectionMatrix());
	shader->set4fv("view", camera->getView());
	shader->set4fv("model", model);
	tex->bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void Player::imgui()
{

	ImGui::DragFloat("Player Speed", &speed, 0.1f, 0.0f, 25.0f, "%.3f", ImGuiSliderFlags_None);

}
