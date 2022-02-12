#pragma once
#include "Component.h"
#include "Texture.h"
class SpriteRenderer : public Component
{
	COMPONENT_TYPE(SpriteRenderer)
public:
	static Ref<SpriteRenderer> createSprite(const std::string& fileName);
	static Ref<SpriteRenderer> createSprite(const std::string& fileName, unsigned int id);
	Ref<Texture> getTexture();
	
	~SpriteRenderer();
private:
	SpriteRenderer(const std::string& fileName);
	SpriteRenderer(const std::string& fileName, unsigned int id);
	Ref<Texture> tex;
};

