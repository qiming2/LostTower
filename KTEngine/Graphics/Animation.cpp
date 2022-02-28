#include "Animation.h"

Ref<Animation> Animation::createAnimation(Ref<Sprite> sprite)
{
	Animation* ptr = new Animation();
	Ref<Animation> ret = Ref<Animation>(ptr);
	ret->m_sprite = sprite;
	ret->m_height = (float)sprite->getTexture()->getHeight();
	ret->m_width = (float)sprite->getTexture()->getHeight();
	ret->m_numFrames = ((float)sprite->getTexture()->getWidth() + 0.1f) / ret->m_height;
	ret->m_curFrame = 0;
	ret->w_spacing = 0.0f;
	ret->h_spacing = 0.0f;
	return ret;
}

Ref<Sprite> Animation::getSpriteSheet() {
	return m_sprite;
}

void Animation::startAnimation() {
	m_curFrame = 0;
	fillSpriteUVs();
}

void Animation::fillSpriteUVs() {
	std::vector<glm::vec2>& uvs = m_sprite->getUVs();
	float leftpadding = (m_width * m_curFrame) / (float)m_sprite->getTexture()->getWidth();
	float width_uv_offset = m_width / (float)(float)m_sprite->getTexture()->getWidth();
	// Fixed 2D texture coord size
	// Harded V coordinate for now
	uvs[1].x = leftpadding;				      uvs[1].y = 0.0f;
	uvs[0].x = leftpadding;					  uvs[0].y = 1.0f;
	uvs[2].x = leftpadding + width_uv_offset; uvs[2].y = 0.0f;
	uvs[3].x = leftpadding;					  uvs[3].y = 1.0f;
	uvs[4].x = leftpadding + width_uv_offset; uvs[4].y = 0.0f;
	uvs[5].x = leftpadding + width_uv_offset; uvs[5].y = 1.0f;
}

bool Animation::isOver() {
	return m_curFrame == m_numFrames - 1;
}

void Animation::nextFrame() {
	if (m_curFrame == m_numFrames - 1) return;

	m_curFrame++;

	fillSpriteUVs();
}

void Animation::changeToFrame(unsigned int index) {
	if (index >= m_numFrames) return;

	m_curFrame = index;
	fillSpriteUVs();
}

Animation::~Animation()
{
}

Animation::Animation()
{
	m_sprite = nullptr;
	m_width = 0.0f;
	m_height = 0.0f;
	m_numFrames = 0;
	m_curFrame = 0;
	w_spacing = 0.0f;
	h_spacing = 0.0f;
}
