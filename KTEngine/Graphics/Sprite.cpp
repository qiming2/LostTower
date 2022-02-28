#include "Sprite.h"
#include "AssetPool.h"

Ref<Sprite> Sprite::createSprite(const std::string& fileName)
{	
	Sprite* ptr = new Sprite();
	Ref<Sprite> ret = Ref<Sprite>(ptr);
	ret->m_tex = AssetPool::getTexture(fileName.c_str());
	return ret;
}

Ref<Sprite> Sprite::createSprite(const std::string& fileName, unsigned int id)
{
	Sprite* ptr = new Sprite();
	Ref<Sprite> ret = Ref<Sprite>(ptr);
	ret->m_tex = AssetPool::getTexture(fileName.c_str(), id);
	return ret;
}

Ref<Sprite> Sprite::createSprite(const std::string& fileName, unsigned int id, unsigned int texFlag)
{
	Sprite* ptr = new Sprite();
	Ref<Sprite> ret = Ref<Sprite>(ptr);
	ret->m_tex = AssetPool::getTexture(fileName.c_str(), id, texFlag);
	return ret;
}

Ref<Texture> Sprite::getTexture()
{
	return m_tex;
}

std::vector<glm::vec2>& Sprite::getUVs()
{
	return m_uvs;
}

Sprite::Sprite():
	m_uvs(TEXTURE_COORD_SIZE_2D)
{
	m_uvs[0] = { 0.0f, 1.0f };
	m_uvs[1] = { 0.0f, 0.0f };
	m_uvs[2] = { 1.0f, 0.0f };
	m_uvs[3] = { 0.0f, 1.0f };
	m_uvs[4] = { 1.0f, 0.0f };
	m_uvs[5] = { 1.0f, 1.0f };
	m_tex = nullptr;
}

Sprite::~Sprite()
{
}
