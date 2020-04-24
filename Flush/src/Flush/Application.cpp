#include "flushpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "GLFW/glfw3.h"

namespace Flush {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		Flush_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		//WindowResizeEvent e(400,400);
		//if (e.IsInCategory(EventCategoryApplication))
		//{
		//	Flush_TRACE(e);
		//}
		//if (e.IsInCategory(EventCategoryInput))
		//{
		//	Flush_TRACE(e);
		//}
		//while (true);

		while (m_Running)
		{
			glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}