#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Flush {
	
	class FLUSH_API Application // __declspec(dllexport)
	{	
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// to be define in client
	Application* CreateApplication();
}


