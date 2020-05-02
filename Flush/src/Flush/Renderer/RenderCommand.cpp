#include "flushpch.h"
#include "RenderCommand.h"


#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Flush {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;	
}