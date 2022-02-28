#include "Texture.h"
#include "STB/stb_image.h"

Texture::Texture(const char* image, unsigned int activeID):
	Texture(image)
{
	m_activeID = activeID;
}

Texture::Texture(const char* image, unsigned int activeID, unsigned int texFlag)
	:Texture(image)
{
	m_activeID = activeID;
	bind();
	if (texFlag & KTexture::CLAMP_TO_EDGE) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	if (texFlag & KTexture::MAG_NEAREST) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	}

	if (texFlag & KTexture::MIN_LINEAR_NEAREST) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	}
	
	unBind();
}

Texture::Texture(const char* image)
{
	m_activeID = 0;
	glGenTextures(1, &m_renderID);

	// STB load image
	int width, height, channel;

	// Flip since opengl has reversed y
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &width, &height, &channel, 0);
	// If image width is not multiple of 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (data) {
		unsigned int channel_type = GL_RGBA;
		if (channel == 1) {
			channel_type = GL_RED;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		}
		else if (channel == 3) {
			channel_type = GL_RGB;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		}
		else if (channel == 4) {
			channel_type = GL_RGBA;
		}
		bind();

		// Create image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, channel_type, GL_UNSIGNED_BYTE, data);

		// Set opengl query parameter
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		
		m_width = width;
		m_height = height;
	}
	else {
		ekp("TEXTURE::LOAD::FAIL\n ----", image);
		m_width = 0;
		m_height = 0;
	}
	stbi_image_free(data);
	unBind();
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_renderID);
}

void Texture::setID(unsigned int activeID)
{
	m_activeID = activeID;
}

unsigned int Texture::getID()
{
	return m_activeID;
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + m_activeID);
	glBindTexture(GL_TEXTURE_2D, m_renderID);
}

void Texture::unBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getWidth() {
	return m_width;
}

unsigned int Texture::getHeight() { 
	return m_height;
}