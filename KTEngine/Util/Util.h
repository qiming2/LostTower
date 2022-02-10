#pragma once
#include <vector>
#include <string>

#ifdef K_DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x;
#endif
#define ASSERT(x) if (!(x)) __debugbreak();
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
class Util
{
public:
	// very unefficient, thus use it for simple parsing
	static std::vector<std::string> split(std::string s, const std::string& delim);
	static std::vector<float> spriteQuad();
private:
};

