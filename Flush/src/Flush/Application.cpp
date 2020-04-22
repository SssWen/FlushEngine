#include "flushpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Flush {

	Application::Application()
	{

	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		WindowResizeEvent e(400,400);
		if (e.IsInCategory(EventCategoryApplication))
		{
			Flush_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			Flush_TRACE(e);
		}
		while (true);
	}
}