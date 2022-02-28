#include <vector>
#include "Monster.h"
#include "Util/Util.h"
#include "SpriteRenderer.h"
#include "Texture.h"

Monster::Monster() :
	GameObject()
{
	// test renderer and spriteRenderer

	//addComponent(SpriteRenderer::createSprite("LostTower\\Asset\\se_1.jpg", 4));
	transform.changeScale(glm::vec3(96.0f, 96.0f, 1.0f));
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
