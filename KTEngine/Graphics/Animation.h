#pragma once
#include "Sprite.h"


// Currently only support spritesheet animations
	// maybe need to add list-of-sprite animation support later
class Animation
{
public:
	

	// Assume height offset is 0, texture height is the m_width_offset and
	// numFrames to be Texture width / Texture Height
	static Ref<Animation> createAnimation(Ref<Sprite>);
	void startAnimation();
	Ref<Sprite> getSpriteSheet();
	void nextFrame();
	void changeToFrame(unsigned int);
	bool isOver();
	~Animation();
private:
	void fillSpriteUVs();
	Animation();
	// Holding a sprite sheet
	Ref<Sprite> m_sprite;
	float m_width;
	float m_height;
	unsigned int m_numFrames;
	unsigned int m_curFrame;

	// Does not make sense right
	float w_spacing;
	float h_spacing;
};

