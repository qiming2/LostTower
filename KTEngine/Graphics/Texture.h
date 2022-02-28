#pragma once
#include "Common.h"

//////////////////--- TEXTURE FLAG ---////////////////////////
namespace KTexture {
	enum flags {
		CLAMP_TO_EDGE = 0x01,
		MAG_NEAREST = 0x02,
		MAG_LINEAR = 0x04,
		MIN_LINEAR_LINEAER = 0x08,
		MIN_LINEAR_NEAREST = 0x010,
		MIN_NEAREST_LINEAR = 0x020,
	};
}
/////////////////////////////////////////

class Texture
{
public:
	Texture(const char* image, unsigned int activeID);
	Texture(const char* image, unsigned int activeID, unsigned int texFlag);
	Texture(const char* image);
	~Texture();
	void setID(unsigned int activeID);
	unsigned int getID();
	void bind();
	void unBind();
	unsigned int getWidth();
	unsigned int getHeight();
private:
	unsigned int m_activeID;
	unsigned int m_renderID;
	unsigned int m_width, m_height;
};

