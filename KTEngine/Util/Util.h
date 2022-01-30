#pragma once
#include <vector>
#include <string>
class Util
{
public:
	// very unefficient, thus use it for simple parsing
	static std::vector<std::string> split(std::string s, const std::string& delim);
private:
};

