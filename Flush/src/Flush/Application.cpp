#include "flushpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "GLFW/glfw3.h"

namespace Flush {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{

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
}