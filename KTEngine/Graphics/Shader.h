#pragma once
#include <vector>
#include "Common.h"
#include "GLM/glm.hpp"

class Shader
{
public:
	Shader(const char* filepath);
	~Shader();
	void bind();
	void unBind();
	void set3f(const std::string& name, const glm::vec3& v);
	void set4f(const std::string& name, const glm::vec4& v);
	void set2f(const std::string& name, const float& v0, const float& v1);
	void setf(const std::string& name, const float& f);
	void seti(const std::string& name, const int& i);
	void setiArray(const std::string& name, const int& count, const int* i);
	void set3fv(const std::string& name, const glm::mat3& m);
	void set4fv(const std::string& name, const glm::mat4& m);
	std::string m_filePath;
private:
	unsigned int m_renderID;
	std::vector<std::pair<std::string, int>> location_cache;
	unsigned int compileShader(const char* code, unsigned int type);
	int getLocation(const std::string& name);
};

