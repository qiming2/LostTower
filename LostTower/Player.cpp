#include <vector>
#include "Player.h"
#include "Util/Util.h"
#include "AssetPool.h"
#include "SpriteRenderer.h"
#include "Animation.h"
#include "Animator.h"
#include "Sprite.h"
#include "Collider2D.h"


namespace KPlayer {
	enum player_state {
		IDLE = 0x0,
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
	};
}

Player::Player() :
	GameObject()
{
	addComponent(SpriteRenderer::createSpriteRenderer());
	addComponent(Animator::createAnimator(4));
	addComponent(Collider2D::createCollider2D(ColliderType::Circle));
	unsigned int texFlag = KTexture::CLAMP_TO_EDGE | KTexture::MAG_NEAREST;
	Ref<Sprite> sprite = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack1.png", 5, texFlag);
	Ref<Sprite> sprite1 = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack2.png", 5, texFlag);
	Ref<Sprite> sprite2 = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack3.png", 5, texFlag);
	Ref<Sprite> sprite3 = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter.png", 5, texFlag);
	// Test animation
	
	Ref<Animation> anime = Animation::createAnimation(sprite);
	Ref<Animation> anime1 = Animation::createAnimation(sprite1);
	Ref<Animation> anime2 = Animation::createAnimation(sprite2);
	Ref<Animation> anime3 = Animation::createAnimation(sprite3);
	
	Ref<Animator> animator = getComponentByType<Animator>();
	animator->addAnimation(anime, KPlayer::ATTACK_1);
	animator->addAnimation(anime1, KPlayer::ATTACK_2);
	animator->addAnimation(anime2, KPlayer::ATTACK_3);
	animator->addAnimation(anime3, KPlayer::IDLE);
	animator->setAnimation(KPlayer::IDLE, KAnimator::LOOPING);
	// Add collision component
	/*Ref<Sprite> sprite = Sprite::createSprite("LostTower\\Asset\\se_1.jpg", 0);
	addComponent(SpriteRenderer::createSpriteRenderer(sprite));*/
	speed = 5.0f;
	transform.move(glm::vec3(0.0f, 3.0f, 0.0f), 250.0f);
	transform.changeScale(glm::vec3(144.0f, 144.0f, 1.0f));
}

Player::~Player()
{
}

void Player::update(float dt)
{
	if (KeyListener::isKeyDown(GLFW_KEY_W) || KeyListener::isKeyDown(GLFW_KEY_UP)) {
		transform.move(glm::vec3(0.0f, 1.0f, 0.0f), speed);

	}
	else if (KeyListener::isKeyDown(GLFW_KEY_S) || KeyListener::isKeyDown(GLFW_KEY_DOWN)) {
		transform.move(glm::vec3(0.0f, -1.0f, 0.0f), speed);
	}
	else if (KeyListener::isKeyDown(GLFW_KEY_A) || KeyListener::isKeyDown(GLFW_KEY_LEFT)) {
		transform.move(glm::vec3(-1.0f, 0.0f, 0.0f), speed);
		if (transform.scale[0] > 0.0f) {
			transform.scale[0] = -transform.scale[0];
		}
	}
	else if (KeyListener::isKeyDown(GLFW_KEY_D) || KeyListener::isKeyDown(GLFW_KEY_RIGHT)) {
		transform.move(glm::vec3(1.0f, 0.0f, 0.0f), speed);
		if (transform.scale[0] < 0.0f) {
			transform.scale[0] = -transform.scale[0];
		}
	}
	
	static unsigned int temp_index = 1;
	if (KeyListener::isKeyPressed(GLFW_KEY_SPACE)) {
		temp_index = (temp_index + 1) % 4;
		getComponentByType<Animator>()->setAnimation(temp_index, KAnimator::LOOPING);
	}
	//transform.rotate(glm::vec3(0.0f, 0.0f, dt));
	getComponentByType<Animator>()->update(dt);
}

void Player::imgui()
{

	ImGui::DragFloat("Player Speed", &speed, 0.1f, 0.0f, 25.0f, "%.3f", ImGuiSliderFlags_None);

}
