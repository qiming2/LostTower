#include <vector>
#include "Monster.h"
#include "Util/Util.h"
#include "SpriteRenderer.h"

Monster::Monster() :
	GameObject()
{

	// test renderer and spriteRenderer
	addComponent(SpriteRenderer::createSprite("LostTower\\Asset\\se_1.jpg", 4));
	speed = 5.0f;
}

Monster::~Monster()
{
}

void Monster::update(float dt)
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

}

void Monster::imgui()
{

	ImGui::DragFloat("Monster Speed", &speed, 0.1f, 0.0f, 25.0f, "%.3f", ImGuiSliderFlags_None);
	//ImGui::Text("SpriteRenderer Component Exists? : %d", getComponentByType(ComponentType::SpriteRenderer)->getCompName().c_str() != nullptr);
}
