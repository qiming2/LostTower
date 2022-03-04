#include <vector>
#include "Monster.h"
#include "Util/Util.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Animator.h"
#include "Collider2D.h"

namespace KMonster {
	enum monster_state {
		IDLE = 0x0,
		ATTACK_1,
		ATTACK_2,
		ATTACK_3,
		ATTACKED,
		LAST_STATE,
	};
}

Monster::Monster() :
	GameObject("Monster")
{
	addComponent(SpriteRenderer::createSpriteRenderer());
	addComponent(Animator::createAnimator(KMonster::LAST_STATE));
	addComponent(Collider2D::createCollider2D(ColliderType::Polygon));
	unsigned int texFlag = KTexture::CLAMP_TO_EDGE | KTexture::MAG_NEAREST;
	Ref<Sprite> sprite = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack1.png", 5, texFlag);
	Ref<Sprite> sprite1 = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack2.png", 5, texFlag);
	Ref<Sprite> sprite2 = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack3.png", 5, texFlag);
	Ref<Sprite> sprite3 = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter.png", 5, texFlag);
	Ref<Sprite> sprite4 = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_hurt.png", 5, texFlag);
	// Test animation

	Ref<Animation> anime = Animation::createAnimation(sprite);
	Ref<Animation> anime1 = Animation::createAnimation(sprite1);
	Ref<Animation> anime2 = Animation::createAnimation(sprite2);
	Ref<Animation> anime3 = Animation::createAnimation(sprite3);
	Ref<Animation> anime4 = Animation::createAnimation(sprite4);

	Ref<Animator> animator = getComponentByType<Animator>();
	animator->addAnimation(anime,  KMonster::ATTACK_1);
	animator->addAnimation(anime1, KMonster::ATTACK_2);
	animator->addAnimation(anime2, KMonster::ATTACK_3);
	animator->addAnimation(anime3, KMonster::IDLE);
	animator->addAnimation(anime4, KMonster::ATTACKED);
	animator->setAnimation(KMonster::IDLE, KAnimator::LOOPING);
	transform.changeScale(glm::vec3(144.0f, 144.0f, 1.0f));


}

Monster::~Monster()
{
}

void Monster::update(float dt)
{
	getComponentByType<Animator>()->update(dt);
}

void Monster::imgui()
{

	ImGui::DragFloat("Monster Speed", &speed, 0.1f, 0.0f, 25.0f, "%.3f", ImGuiSliderFlags_None);

}

void Monster::onTrigger(Collider2D * other) {
	static bool isAttacked = false;
	if (other->gameObject->tag == std::string("Player") && !isAttacked) {
		kp("Hello");
		isAttacked = true;
		getComponentByType<Animator>()->setAnimation(KMonster::ATTACKED, 0);
	}
}