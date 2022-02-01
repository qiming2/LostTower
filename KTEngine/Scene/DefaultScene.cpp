#include <vector>
#include "DefaultScene.h"
#include "DefaultScene.h"
#include "IMGUI/imgui.h"
#include "Window.h"

//////////////////////////////////////// Temporary Debug Tool /////////////////
#define ASSERT(x) if (!(x)) __debugbreak();
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

///////////////////////////////////////////////////////////////////////////////

DefaultScene::DefaultScene()
{
	std::vector<float> vertices = {
		 -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// vao, vbo set up
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), (void*)vertices.data(), GL_STATIC_DRAW));

	// vertex attribute
	
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	shader = std::make_shared<Shader>("KTEngine/Asset/Shader/default.glsl");
	
	glBindVertexArray(0);
}

DefaultScene::DefaultScene(const std::string& name)
{
	this->scene_name = name;
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::update(float dt)
{
	
	GLCall(glBindVertexArray(vao));
	shader->bind();
	shader->setf("u_Time", Window::getTime());
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void DefaultScene::imgui()
{
	ImGui::Begin("This is a Default Scene!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", (float)(Window::getFrameRate() * 1000.0f), 1.0f / Window::getFrameRate());
	ImGui::End();
}
