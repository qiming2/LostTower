#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"


IMP_COMPONENT_TYPE(Animator);

Animator::~Animator() {

}

Animator::Animator(unsigned int max_anime_num) :
	m_animations(max_anime_num),
	m_anime_num(0),
	m_fpsAnime(DEFAULT_ANIMATION_SPEED),
	timer(0.0f),
	isRunning(false)
{

}

void Animator::addAnimation(Ref<Animation> anime, unsigned int index) {
	if (m_animations[index] != nullptr) return;
	m_animations[index] = anime;
	m_anime_num++;
}

Ref<Animator> Animator::createAnimator(unsigned int max_anime_num) {
	Animator* ptr = new Animator(max_anime_num);
	Ref<Animator> ret = Ref<Animator>(ptr);
	return ret;
}

void Animator::setAnimation(unsigned int index, unsigned int flags) {
	if (index >= m_anime_num) return;
	m_cur_anime_index = index;
	m_cur_flags = flags;
	isRunning = true;
	setAnimation();
}

void Animator::setAnimation(unsigned int index, unsigned int flags, float fpsAnime) {
	if (index >= m_anime_num) return;
	m_cur_anime_index = index;
	m_cur_flags = flags;
	m_fpsAnime = fpsAnime;
	isRunning = true;
	setAnimation();
}

void Animator::update(float dt) {
	if (!isRunning) return;
	timer += dt;
	if (timer >= m_fpsAnime) {
		if (m_animations[m_cur_anime_index]->isOver()) {
			if (m_cur_flags & KAnimator::LOOPING) {
				m_animations[m_cur_anime_index]->startAnimation();
			}
			else {
				reset();
			}
		} else {
			m_animations[m_cur_anime_index]->nextFrame();
		}
		timer = 0.0f;
	}
}

void Animator::setAnimation() {
	Ref<SpriteRenderer> sp;
	if (gameObject) {
		sp = gameObject->getComponentByType<SpriteRenderer>();
		if (sp) {
			sp->changeSprite(m_animations[m_cur_anime_index]->getSpriteSheet());
			m_animations[m_cur_anime_index]->startAnimation();
		} else {
			ekp("No SpriteRenderer Component");
		}
	}
	else {
		reset();
		ekp("Not associated with a game object");
	}
}

void Animator::reset() {
	m_cur_anime_index = 0;
	m_cur_flags = 0;
	m_fpsAnime = DEFAULT_ANIMATION_SPEED;
	timer = 0.0f;
	isRunning = false;
}

