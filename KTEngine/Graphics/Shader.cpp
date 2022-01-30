#include "Shader.h"
#include "Util/FileUtil.h"
#include "Util/Util.h"

Shader::Shader(const char* filepath)
{
	// Parse string
	std::string code = FileUtil::readAll(filepath);
	std::vector<std::string> shaders_s = Util::split(code, "#");
}

Shader::~Shader()
{
}

void Shader::bind()
{
}

void Shader::unBind()
{
}

void Shader::set3f(const std::string& name, const glm::vec3& v)
{
}

void Shader::set4f(const std::string& name, const glm::vec4& v)
{
}

void Shader::seti(const std::string& name, const int& i)
{
}

void Shader::setf(const std::string& name, const float& f)
{
}

void Shader::set3fv(const std::string& name, const glm::mat3& m)
{
}

void Shader::set4fv(const std::string& name, const glm::mat4& m)
{
}

unsigned int Shader::compileShader(const char* code, unsigned int type)
{
	return 0;
}

int Shader::getLocation(const std::string& name)
{
	return 0;
}
