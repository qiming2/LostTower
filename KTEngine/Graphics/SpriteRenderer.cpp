#include <memory>
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "AssetPool.h"

SpriteRenderer::SpriteRenderer(const std::string& fileName) {
	tex = AssetPool::getTexture(fileName.c_str());

} 

SpriteRenderer::SpriteRenderer(const std::string& fileName, unsigned int id) {
	tex = AssetPool::getTexture(fileName.c_str(), id);

}

IMP_COMPONENT_TYPE(SpriteRenderer)

Ref<SpriteRenderer> SpriteRenderer::createSprite(const std::string& fileName) {
	SpriteRenderer* newSprite = new SpriteRenderer(fileName);
	Ref<SpriteRenderer> newSpriteRef(newSprite);
	Renderer::getInstance()->addSpriteRenderer(newSpriteRef);
	return newSpriteRef;
}

Ref<SpriteRenderer> SpriteRenderer::createSprite(const std::string& fileName, unsigned int id) {
	SpriteRenderer* newSprite = new SpriteRenderer(fileName, id);
	Ref<SpriteRenderer> newSpriteRef(newSprite);
	Renderer::getInstance()->addSpriteRenderer(newSpriteRef);
	return newSpriteRef;
}

Ref<Texture> SpriteRenderer::getTexture()
{
	return tex;
}
SpriteRenderer::~SpriteRenderer()
{
}
