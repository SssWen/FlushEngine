#include "flushpch.h"
#include "Shader.h"

#include "glad/glad.h"
#include "Log.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Flush{

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		//case RendererAPI::API::None:    FLUSH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		//FLUSH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}