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
#ifdef K_DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x;
#endif
///////////////////////////////////////////////////////////////////////////////

DefaultScene::DefaultScene()
{
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};
	std::vector<float> screenQuadVertices = {
		// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f

	};
	// vao, vbo set up
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	GLCall(glGenBuffers(1, &vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, screenQuadVertices.size() * sizeof(float), (void*)screenQuadVertices.data(), GL_STATIC_DRAW));

	// vertex attribute
	
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float)*2)));
	GLCall(glEnableVertexAttribArray(1));
	shader = std::make_shared<Shader>("KTEngine/Asset/Shader/default.glsl");

	int id = 2;
	tex = std::make_shared<Texture>("KTEngine\\Asset\\Image\\GI\\hutao_4k.jpg", id);
	shader->bind();
	shader->seti("tex", id);
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
	shader->set2f("u_Resolution", Window::getWidth(), Window::getHeight());
	shader->setf("u_Time", Window::getTime());
	tex->bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void DefaultScene::imgui()
{
	ImGui::Begin("This is a Default Scene!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", (float)(Window::getFrameRate() * 1000.0f), 1.0f / Window::getFrameRate());
	ImGui::End();
}
