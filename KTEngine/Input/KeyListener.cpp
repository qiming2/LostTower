#include "KeyListener.h"

Ref<KeyListener> KeyListener::getInstance()
{
    static Ref<KeyListener> instance = Ref<KeyListener>(new KeyListener());
    return instance;
}

bool KeyListener::isKeyPressed(int key)
{
    if (key < 0 || key > GLFW_KEY_LAST) return false;
    return getInstance()->keys[key];
}

void KeyListener::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UNKNOWN) return;
    if (action == GLFW_PRESS) {
        getInstance()->keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        getInstance()->keys[key] = false;
    }
    // GLFW_REPEAT
    else {

    }
}

KeyListener::KeyListener()
{
    memset(keys, 0, sizeof(keys));
}


