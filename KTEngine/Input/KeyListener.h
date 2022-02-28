#pragma once
#include "Common.h"

class KeyListener
{
public:
	static Ref<KeyListener> getInstance();
	static bool isKeyPressed(int key);
	static bool isKeyDown(int key);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void endFrame();
private:
	KeyListener();
	unsigned int keys[GLFW_KEY_LAST+1];
};
