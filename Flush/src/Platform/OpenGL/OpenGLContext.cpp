#include "flushpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core/Log.h"

namespace Flush 
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		// windowhandle is null
	}

	void OpenGLContext::Init() 
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		Flush_CORE_INFO("OpenGL Info: ");
		Flush_CORE_INFO(" Vendor: {0} ", glGetString(GL_VENDOR));		
		Flush_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));		
		Flush_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));
		
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}