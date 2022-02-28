#include <memory>
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "AssetPool.h"


IMP_COMPONENT_TYPE(SpriteRenderer)

SpriteRenderer::SpriteRenderer(Ref<Sprite> sprite) :
	Component()
{
	m_sprite = sprite;
}

SpriteRenderer::SpriteRenderer() :
	Component()
{
	m_sprite = nullptr;
}

Ref<SpriteRenderer> SpriteRenderer::createSpriteRenderer(Ref<Sprite> sprite) {
	SpriteRenderer* ptr = new SpriteRenderer(sprite);
	Ref<SpriteRenderer> ret = Ref<SpriteRenderer>(ptr);
	Renderer::getInstance()->addSpriteRenderer(ret);
	return ret;
}

Ref<SpriteRenderer> SpriteRenderer::createSpriteRenderer() {
	SpriteRenderer* ptr = new SpriteRenderer();
	Ref<SpriteRenderer> ret = Ref<SpriteRenderer>(ptr);
	Renderer::getInstance()->addSpriteRenderer(ret);
	return ret;
}


void SpriteRenderer::changeSprite(Ref<Sprite> newS)
{
	m_sprite = newS;
}

Ref<Sprite> SpriteRenderer::getSprite()
{
	return m_sprite;
}
SpriteRenderer::~SpriteRenderer()
{
}
