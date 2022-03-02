#include <vector>
#include "Monster.h"
#include "Util/Util.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Animator.h"
#include "Collider2D.h"

Monster::Monster() :
	GameObject()
{
	// test renderer and spriteRenderer
	addComponent(SpriteRenderer::createSpriteRenderer());
	addComponent(Animator::createAnimator(1));
	addComponent(Collider2D::createCollider2D(ColliderType::Circle));
	unsigned int texFlag = KTexture::CLAMP_TO_EDGE | KTexture::MAG_NEAREST;
	Ref<Sprite> sprite = Sprite::createSprite("KTEngine\\Asset\\SpriteSheets\\sample_art\\Woodcutter\\Woodcutter_attack1.png", 5, texFlag);
	Ref<Animation> anime = Animation::createAnimation(sprite);
	Ref<Animator> animator = getComponentByType<Animator>();
	animator->addAnimation(anime, 0);
	animator->setAnimation(0, KAnimator::LOOPING);
	transform.changeScale(glm::vec3(144.0f, 144.0f, 1.0f));
}

Monster::~Monster()
{
}

void Monster::update(float dt)
{
}

void Monster::imgui()
{

	ImGui::DragFloat("Monster Speed", &speed, 0.1f, 0.0f, 25.0f, "%.3f", ImGuiSliderFlags_None);
	//ImGui::Text("SpriteRenderer Component Exists? : %d", getComponentByType(ComponentType::SpriteRenderer)->getCompName().c_str() != nullptr);
}
