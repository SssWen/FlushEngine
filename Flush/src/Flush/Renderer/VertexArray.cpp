#include "flushpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Flush {

	//VertexArray* VertexArray::Create()
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		//case RendererAPI::None:    FLUSH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}

		//FLUSH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}