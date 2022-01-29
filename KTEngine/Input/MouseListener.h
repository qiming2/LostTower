#pragma once
#include "Common.h"

class MouseListener
{
public:
	static Ref<MouseListener> getInstance();
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void endFrame();
	static float getX();
	static float getY();
	static float getDx();
	static float getDy();
	static float getScrollX();
	static float getScrollY();
	static bool dragging();
	static bool isMouseButtonDown(int button);
private:
	MouseListener();
	double scrollX, scrollY;
	double xPos, yPos, lastX, lastY;
	bool mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
	bool isDragging;
};

