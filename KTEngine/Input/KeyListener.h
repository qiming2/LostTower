#pragma once
#include "Common.h"

class KeyListener
{
public:
	static Ref<KeyListener> getInstance();
	static bool isKeyPressed(int key);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	KeyListener();
	bool keys[GLFW_KEY_LAST+1];
};
