#include "Texture.h"
#include "STB/stb_image.h"

Texture::Texture(const char* image, unsigned int activeID)
{
	m_activeID = activeID;
	glGenTextures(1, &m_renderID);
	
	// STB load image
	int width, height, channel;
	
	// Flip since opengl has reversed y
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &width, &height, &channel, 0);
	// If image width is not multiple of 4
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (data) {
		unsigned int channel_type = GL_RGB;
		if (channel == 1) {
			channel_type = GL_RED;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		}
		else if (channel == 3) {
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	}
	else {
		ekp("TEXTURE::LOAD::FAIL\n ----", image);
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

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + m_activeID);
	glBindTexture(GL_TEXTURE_2D, m_renderID);
}

void Texture::unBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
