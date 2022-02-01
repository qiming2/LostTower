#pragma once
#include "Common.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Scene/Scene.h"
#include "Scene/LevelEditor.h"

class Window
{
public:
	static Ref<Window> getInstance();
	static void errorCallback(int error, const char* description);
	static void framebufferCallback(GLFWwindow* window, int width, int height);
	static void setWidth(int width);
	static void setHeight(int height);
	static int getWidth();
	static int getHeight();
	static float getFrameRate();
	static void run();
	static float getTime();
private:
	int width, height;
	std::string window_title;
	Window();
	void init();
	void loop();
	void close();
	GLFWwindow* window;
	glm::vec3 bg_color;
	double prev_time;
	double cur_time;
};


