#pragma once
#include <vector>
#include "GLM/glm.hpp"
#include "Common.h"
#include "Texture.h"

// 6 glm::vec2 type
#define TEXTURE_COORD_SIZE_2D 6

class Sprite
{
public:
	static Ref<Sprite>	createSprite(const std::string& fileName);
	static Ref<Sprite>	createSprite(const std::string& fileName, unsigned int id);
	static Ref<Sprite>	createSprite(const std::string& fileName, unsigned int id, unsigned int texFlag);
	Ref<Texture> getTexture();

	// can be used to change the uvs or send to the gpu
	std::vector<glm::vec2>& getUVs();
	
	~Sprite();
private:
	Sprite();
	std::vector<glm::vec2> m_uvs;
	Ref<Texture> m_tex;
};

