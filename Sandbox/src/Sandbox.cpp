
#include <Flush.h>
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"
#include "ExampleLayer.h"
#include "Core/EntryPoint.h"

class Sandbox : public Flush::Application
{
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());				
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {

	}
};

Flush::Application* Flush::CreateApplication()
{
	return new Sandbox();
}