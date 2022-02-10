#include "AssetPool.h"

Ref<Texture> AssetPool::getTexture(const std::string& fileName)
{
	AssetPool* instance = getInstance();
	std::unordered_map<std::string, Ref<Texture>>::iterator it;
	if ((it = instance->textures.find(fileName)) != instance->textures.end()) {
		return it->second;
	}
	Ref<Texture> newTex = std::make_shared<Texture>(fileName.c_str());
	instance->textures.insert({ fileName, newTex });
	return newTex;
}

Ref<Texture> AssetPool::getTexture(const std::string& fileName, unsigned int id)
{
	AssetPool* instance = getInstance();
	std::unordered_map<std::string, Ref<Texture>>::iterator it;
	if ((it = instance->textures.find(fileName)) != instance->textures.end()) {
		return it->second;
	}
	Ref<Texture> newTex = std::make_shared<Texture>(fileName.c_str(), id);
	instance->textures.insert({ fileName, newTex });
	return newTex;
}

Ref<Shader> AssetPool::getShader(const std::string& fileName)
{
	AssetPool* instance = getInstance();
	std::unordered_map<std::string, Ref<Shader>>::iterator it;
	if ((it = instance->shaders.find(fileName)) != instance->shaders.end()) {
		return it->second;
	}
	Ref<Shader> newShader = std::make_shared<Shader>(fileName.c_str());
	instance->shaders.insert({ fileName, newShader });
	return newShader;
}

AssetPool* AssetPool::getInstance()
{
	static AssetPool* _instance = new AssetPool;
	return _instance;
}

AssetPool::AssetPool()
{
}

AssetPool::~AssetPool()
{
}
