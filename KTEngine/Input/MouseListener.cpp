#include "MouseListener.h"

MouseListener::MouseListener()
{
	xPos, yPos, lastX, lastY, scrollX, scrollY = 0.0;
	isDragging = false;
	memset(mouseButtons, 0, sizeof(mouseButtons));
}

Ref<MouseListener> MouseListener::getInstance()
{
	static Ref<MouseListener> listener = Ref<MouseListener>(new MouseListener());
	return listener;
}

void MouseListener::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	getInstance()->lastX = xpos;
	getInstance()->lastY = ypos;
	getInstance()->xPos = xpos;
	getInstance()->yPos = ypos;

	// Only check if left or right mouse are dragging
	getInstance()->isDragging = getInstance()->mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) || getInstance()->mouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT);
}

void MouseListener::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Ref<MouseListener> listener = getInstance();
	if (action == GLFW_PRESS) {
		listener->mouseButtons[button] = true;
		//kp("button ", button, " is pressed: ", listener->mouseButtons[button]);
	}
	else {
		listener->mouseButtons[button] = false;
		if (!getInstance()->mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !getInstance()->mouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
			listener->isDragging = false;
		}
	}

	
}

void MouseListener::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	getInstance()->scrollX = xoffset;
	getInstance()->scrollY = yoffset;
}

void MouseListener::endFrame()
{
	getInstance()->scrollX = 0;
	getInstance()->scrollY = 0;
	getInstance()->lastX = getInstance()->xPos;
	getInstance()->lastY = getInstance()->yPos;
}

float MouseListener::getX()
{
	return getInstance()->xPos;
}

float MouseListener::getY()
{
	return getInstance()->yPos;
}

float MouseListener::getDx()
{
	return (getInstance()->xPos - getInstance()->lastX);
}

float MouseListener::getDy()
{
	return (getInstance()->yPos - getInstance()->lastY);
}

float MouseListener::getScrollX()
{
	return getInstance()->scrollX;
}

float MouseListener::getScrollY()
{
	return getInstance()->scrollY;
}

bool MouseListener::dragging()
{
	return getInstance()->isDragging;
}

bool MouseListener::mouseButtonDown(int button)
{
	if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST) {
		ekp("UNKNOWN BUTTON: ", button);
		return false;
	}
	
	return getInstance()->mouseButtons[button];
		

}
