#pragma once
#include "Component.h"
#include "Common.h"
#include "Animation.h"

#define DEFAULT_ANIMATION_SPEED 1.0f / 15.0f

namespace KAnimator {
	enum flags {
		LOOPING = 0x01,
	};
}

class Animator : public Component
{
	COMPONENT_TYPE(Animator);
public:
	static Ref<Animator> createAnimator(unsigned int max_anime_num);
	void addAnimation(Ref<Animation> anime, unsigned int index);
	void setAnimation(unsigned int index, unsigned int flags);
	void setAnimation(unsigned int index, unsigned int flags, float fpsAnime);
	void update(float dt);
	~Animator();
private:
	Animator(unsigned int max_anime_num);
	void reset();
	void setAnimation();
	std::vector<Ref<Animation>> m_animations;
	unsigned int m_anime_num;

	// Since there can only be one sprite rendered each time 
	// we only need to take care of the current animation
	unsigned int m_cur_anime_index;
	unsigned int m_cur_flags;
	float m_fpsAnime;
	float timer;
	bool isRunning;
};

