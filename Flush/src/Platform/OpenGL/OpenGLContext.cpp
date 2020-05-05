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

#ifdef FLUSH_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		// Check for Opengl Version
		FLUSH_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "FlushEngine requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}