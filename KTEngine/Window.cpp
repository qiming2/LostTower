#include "Window.h"
#include "Input/MouseListener.h"
#include "Input/KeyListener.h"
#include "Util/FileUtil.h"
#include "Scene/SceneManager.h"
#include "Scene/DefaultScene.h"
#include "Renderer.h"

Ref<Window> Window::getInstance()
{
	static Ref<Window> window = Ref<Window>(new Window());
	return window;
}

Window::Window()
{
	// Init all the things like opengl, glfw, imgui, etc.
	init();
	
	// set background color to white
	bg_color[0] = 0.0f;
	bg_color[1] = 1.0f;
	bg_color[2] = 1.0f;
	prev_time = 0.0;
	cur_time = 0.0;
}

// Window, callback, opengl context, imgui context setup
void Window::init() {
	if (!glfwInit()) {
		ekp("GLFW can not be initialized");
	}
	// Setup error callback
	glfwSetErrorCallback(Window::errorCallback);
	
	// window hint
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a window
	width = 1920;
	height = 1080;
	window_title = "Lost Tower";
	window = glfwCreateWindow(width, height, window_title.c_str(), nullptr, nullptr);
	if (!window) {
		ekp("Winodw or context creation failed");
		glfwTerminate();
	}

	// Frambuffer callback
	glfwSetFramebufferSizeCallback(window, Window::framebufferCallback);
	
	// mouse config
	glfwSetCursorPosCallback(window, MouseListener::mouseCallback);
	glfwSetMouseButtonCallback(window, MouseListener::mouseButtonCallback);
	glfwSetScrollCallback(window, MouseListener::mouseScrollCallback);
	glfwMakeContextCurrent(window);
	
	// Keyboard config
	glfwSetKeyCallback(window, KeyListener::keyCallback);

	// glad init
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!status) {
		ekp("Glad load failed");
	}
	// vsync
	glfwSwapInterval(1);

	//imgui set up
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.IniFilename = "imgui.ini";

	// Add font
	io.Fonts->AddFontFromFileTTF("KTEngine/Asset/Font/seguihis.ttf", 20);

	// Dark Theme
	ImGui::StyleColorsDark();

	const char* glsl_version = "#version 460";
	// Platform specific
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// System set up

	// SceneManager Setup
	SceneManager::registerScene<DefaultScene>("Default Scene");
	SceneManager::registerScene<LevelEditor>("Level Editor Scene");
	SceneManager::changeScene("Default Scene");
}

void Window::errorCallback(int error, const char* description) {
	ekp(description);
}

void Window::framebufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window::getInstance()->setHeight(height);
	Window::getInstance()->setWidth(width);
}

void Window::setWidth(int width)
{
	getInstance()->width = width;
}

void Window::setHeight(int height)
{
	getInstance()->height = height;
}

int Window::getWidth()
{
	return getInstance()->width;
}

int Window::getHeight()
{
	return getInstance()->height;
}

float Window::getFrameRate()
{
	return (float)(getInstance()->cur_time - getInstance()->prev_time);
}

void Window::run() {
	getInstance()->loop();
	getInstance()->close();
}

float Window::getTime()
{
	return (float)glfwGetTime();
}

void Window::loop () {
	static bool show_demo_window = true;
	float dt = 0.0f;
	
	// GL_DEPTH_BUFFERE_BIT also needs to be cleared!
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		dt = (float)(cur_time - prev_time);
		// ImGui Rendering
		// glClear needs to come before everything!
		glClearColor(bg_color[0], bg_color[1], bg_color[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// processInput before game
		if (KeyListener::isKeyPressed(GLFW_KEY_ESCAPE)) {
			
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}


		//if (KeyListener::isKeyPressed(GLFW_KEY_C)) {
		//	// Test change scene
		//	SceneManager::changeScene("Level Editor Scene");
		//}

		//if (KeyListener::isKeyPressed(GLFW_KEY_D)) {
		//	// Test change scene
		//	SceneManager::changeScene("Default Scene");
		//}


		// Game Logic
		SceneManager::update(dt);




		// Rendering
		Renderer::getInstance()->renderSpriteSheet();
		

		// Always showing demo window to learn more about imgui
		// usage
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		{
			/*ImGui::Begin("Hello Lost Tower!");
			ImGui::ColorEdit3("Background Color", &bg_color[0]);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", (float)dt * 1000.0f, 1.0f / dt);
			ImGui::End();*/
		}
		
		SceneManager::imgui();
		

		// ImGui Render needs to be after glClearColor();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// swap buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
		prev_time = cur_time;
		cur_time = glfwGetTime();
	}

}

void Window::close() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}