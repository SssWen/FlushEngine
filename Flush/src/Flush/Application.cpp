#include "flushpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "glad/glad.h"
#include "Flush/Input.h"
#include "Flush/Renderer/Renderer.h"
#include "Flush/Core/Timestep.h"

#include <glfw/glfw3.h>

namespace Flush {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Flush::ShaderDataType::Float:    return GL_FLOAT;
		case Flush::ShaderDataType::Float2:   return GL_FLOAT;
		case Flush::ShaderDataType::Float3:   return GL_FLOAT;
		case Flush::ShaderDataType::Float4:   return GL_FLOAT;
		case Flush::ShaderDataType::Mat3:     return GL_FLOAT;
		case Flush::ShaderDataType::Mat4:     return GL_FLOAT;
		case Flush::ShaderDataType::Int:      return GL_INT;
		case Flush::ShaderDataType::Int2:     return GL_INT;
		case Flush::ShaderDataType::Int3:     return GL_INT;
		case Flush::ShaderDataType::Int4:     return GL_INT;
		case Flush::ShaderDataType::Bool:     return GL_BOOL;
		}

		//FLUSH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		//FLUSH_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer(); // 创建一个GUI 
		PushOverlay(m_ImGuiLayer);
		

	}



	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		//Flush_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{			
#pragma region --------Update UI-------------
			float time = (float)glfwGetTime();
			auto timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			// draw gui
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender(); // ShowDemoWindow
			m_ImGuiLayer->End();
#pragma endregion

			m_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}