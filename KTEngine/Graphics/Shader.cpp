#include "Shader.h"
#include "Util/FileUtil.h"
#include "Util/Util.h"
#include "GLM/gtc/type_ptr.hpp"

Shader::Shader(const char* filepath):
	m_filePath(filepath)
{
	// Parse string
	std::string code = FileUtil::readAll(filepath);
	// type-delim is very important currently!
	std::vector<std::string> shaders_s = Util::split(code, "#type - delim");

	// create two shaders [0] is vertex and [1] is fragment shader
	unsigned int vert = compileShader(shaders_s[0].c_str(), GL_VERTEX_SHADER);
	unsigned int frag = compileShader(shaders_s[1].c_str(), GL_FRAGMENT_SHADER);
	
	unsigned int program = glCreateProgram();
	
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	
	glLinkProgram(program);
	glValidateProgram(program);

	// Error log
	int success;
	char log[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(log), NULL, log);
		ekp("SHADER::LOAD::FAIL\n ", __FILE__, " passed in: ", filepath);
	}
	glDeleteShader(vert);
	glDeleteShader(frag);
	m_renderID = program;
	unBind();
}

Shader::~Shader()
{
	glDeleteShader(m_renderID);
}

void Shader::bind()
{
	glUseProgram(m_renderID);
}

void Shader::unBind()
{
	glUseProgram(0);
}

void Shader::set3f(const std::string& name, const glm::vec3& v)
{
	int location;
	if ((location = getLocation(name)) < 0) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", name);
		return;
	}
	glUniform3f(location, v[0], v[1], v[2]);
}

void Shader::set4f(const std::string& name, const glm::vec4& v)
{
	int location;
	if ((location = getLocation(name)) < 0) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", name);
		return;
	}
	glUniform4f(location, v[0], v[1], v[2], v[3]);
}

void Shader::set2f(const std::string& name, const float& v0, const float& v1)
{
	int location;
	if ((location = getLocation(name)) < 0) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", name);
		return;
	}
	glUniform2f(location, v0, v1);
}

void Shader::seti(const std::string& name, const int& i)
{
	int location;
	if ((location = getLocation(name)) < 0) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", name);
		return;
	}
	glUniform1i(location, i);
}

void Shader::setf(const std::string& name, const float& f)
{
	int location;
	if ((location = getLocation(name)) < 0) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", name);
		return;
	}
	glUniform1f(location, f);
}

void Shader::set3fv(const std::string& name, const glm::mat3& m)
{
	int location;
	if ((location = getLocation(name)) < 0) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", name);
		return;
	}
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::set4fv(const std::string& name, const glm::mat4& m)
{
	int location;
	if ((location = getLocation(name)) < 0) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", name);
		return;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m));
}

unsigned int Shader::compileShader(const char* code, unsigned int type)
{
	unsigned int shader = glCreateShader(type);

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	int success;
	char log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::string type_s;
		switch (type)
		{
		case(GL_VERTEX_SHADER):
			type_s = "VERTEX";
			break;
		case(GL_FRAGMENT_SHADER):
			type_s = "FRAGMENT";
			break;
		case(GL_GEOMETRY_SHADER):
			type_s = "GEOMETRY";
			break;
		default:
			type_s = "UNKNOWN";
		}

		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		kp(type_s, " SHADER::COMPILE::FAIL\n", log);
	}
	
	return shader;
}

int Shader::getLocation(const std::string& name)
{
	for (const auto& p : location_cache) {
		if (p.first == name) {
			return p.second;
		}
	}

	int location = glGetUniformLocation(m_renderID, name.c_str());
	if (location == -1) {
		kp("UNIFORM::LOCATION::UNKNOWN\n", __FILE__, ": ", m_filePath);
		return location;
	}
	location_cache.emplace_back(name, location);
	return location;
}
