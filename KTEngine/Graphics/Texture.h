#pragma once
#include "Common.h"

class Texture
{
public:
	Texture(const char* image, unsigned int activeID);
	~Texture();
	void setID(unsigned int activeID);
	void bind();
	void unBind();
private:
	unsigned int m_activeID;
	unsigned int m_renderID;
};

