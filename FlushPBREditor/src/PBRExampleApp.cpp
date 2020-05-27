
#include <Flush.h>
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/EntryPoint.h"
#include "PBREditorLayer.h"


class PBRExampleApp : public Flush::Application
{
public:
	PBRExampleApp() 
	{
		PushLayer(new Flush::PBREditorLayer());
	}

	~PBRExampleApp()
	{
		
	}
};

Flush::Application* Flush::CreateApplication()
{	
	return new PBRExampleApp();
}

