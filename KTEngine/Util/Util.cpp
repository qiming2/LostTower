#include "Util.h"

std::vector<std::string> Util::split(std::string s, const std::string& delim)
{
	std::vector<std::string> ret;
	size_t pos;
	while ((pos = s.find(delim)) != std::string::npos) {
		ret.emplace_back(s.substr(0, pos));
		s.erase(0, pos + delim.length());
	}
	ret.emplace_back(s);
	return ret;
}

std::vector<float> Util::spriteQuad() {
	return std::vector<float>{
		-0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  1.0f, 0.0f,

		-0.5f,  0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  1.0f, 1.0f
	};
}
