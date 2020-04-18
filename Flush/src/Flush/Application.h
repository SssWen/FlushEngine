#pragma once

#include "Core.h"

namespace Flush {
	
	class FLUSH_API Application // __declspec(dllexport)
	{	
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// to be define in client
	Application* CreateApplication();
}


