#pragma once
#include <unordered_map>
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"
class AssetPool
{
public:
	static Ref<Texture> getTexture(const std::string& fileName);
	static Ref<Texture> getTexture(const std::string& fileName, unsigned int id);
	static Ref<Shader> getShader(const std::string& fileName);
	static AssetPool* getInstance();
private:
	AssetPool();
	~AssetPool();
	std::unordered_map<std::string, Ref<Texture>> textures;
	std::unordered_map<std::string, Ref<Shader>> shaders;
};

