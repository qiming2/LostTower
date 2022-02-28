#pragma once
#include "Component.h"
#include "Texture.h"
#include "Sprite.h"
class SpriteRenderer : public Component
{
	COMPONENT_TYPE(SpriteRenderer)
public:
	static Ref<SpriteRenderer> createSpriteRenderer(Ref<Sprite>);
	static Ref<SpriteRenderer> createSpriteRenderer();
	void changeSprite(Ref<Sprite>);
	Ref<Sprite> getSprite();
	
	~SpriteRenderer();
private:
	SpriteRenderer(Ref<Sprite>);
	SpriteRenderer();
	Ref<Sprite> m_sprite;
};

