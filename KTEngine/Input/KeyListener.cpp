#include "KeyListener.h"

namespace KKeyListener {
    enum bit_meaning {
        CUR_FRAME_INPUT = 0x01,
        PREV_FRAME_INPUT = 0x02,
        DOWN_INPUT = 0x04,
        MAX_UNSIGNED_INT = 0xFFFFFFFF,
    };
}

Ref<KeyListener> KeyListener::getInstance()
{
    static Ref<KeyListener> instance = Ref<KeyListener>(new KeyListener());
    return instance;
}

bool KeyListener::isKeyPressed(int key)
{
    if (key < 0 || key > GLFW_KEY_LAST) return false;
    return (getInstance()->keys[key] & KKeyListener::CUR_FRAME_INPUT) && !(getInstance()->keys[key] & KKeyListener::PREV_FRAME_INPUT);
}

bool KeyListener::isKeyDown(int key)
{
	if (key < 0 || key > GLFW_KEY_LAST) return false;
	return (getInstance()->keys[key] & KKeyListener::DOWN_INPUT);
}

void KeyListener::endFrame() {
    for (size_t i = 0; i < GLFW_KEY_LAST + 1; ++i) {
        getInstance()->keys[i] = ((BIT(getInstance()->keys[i], 0) << 1) | BIT(getInstance()->keys[i], 2));
    }
}

void KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UNKNOWN) return;
	if (action == GLFW_PRESS) {
        getInstance()->keys[key] |= KKeyListener::CUR_FRAME_INPUT;
        getInstance()->keys[key] |= KKeyListener::DOWN_INPUT;
    }
	else if (action == GLFW_RELEASE) {
        getInstance()->keys[key] &= (KKeyListener::CUR_FRAME_INPUT ^ KKeyListener::MAX_UNSIGNED_INT);
        getInstance()->keys[key] &= (KKeyListener::DOWN_INPUT ^ KKeyListener::MAX_UNSIGNED_INT);
    }
    // GLFW_REPEAT
    else {

    }
}

KeyListener::KeyListener()
{
    memset(keys, 0, sizeof(keys));
}


