#include <vector>
#include "Player.h"
#include "Util/Util.h"
#include "AssetPool.h"
#include "SpriteRenderer.h"


Player::Player() :
	GameObject()
{
	// Add collision component
	addComponent(SpriteRenderer::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack1.png", 3));
	speed = 10.0f;
	transform.move(glm::vec3(0.0f, 3.0f, 0.0f), 200.0f);
	transform.changeScale(glm::vec3(144.0f, 144.0f, 1.0f));
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
		if (transform.scale[0] > 0.0f) {
			transform.scale[0] = -transform.scale[0];
		}
	}
	else if (KeyListener::isKeyPressed(GLFW_KEY_D) || KeyListener::isKeyPressed(GLFW_KEY_RIGHT)) {
		transform.move(glm::vec3(1.0f, 0.0f, 0.0f), speed);
		if (transform.scale[0] < 0.0f) {
			transform.scale[0] = -transform.scale[0];
		}
	}
	
	
	//transform.rotate(glm::vec3(0.0f, 0.0f, dt));

}

void Player::imgui()
{

	ImGui::DragFloat("Player Speed", &speed, 0.1f, 0.0f, 25.0f, "%.3f", ImGuiSliderFlags_None);

}
