#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Flush/LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Flush/ImGui/ImGuiLayer.h"
#include "Flush/Renderer/Shader.h"
#include "Flush/Renderer/Buffer.h"

namespace Flush {
	
	class FLUSH_API Application // __declspec(dllexport)
	{	
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray; // vao		
		std::unique_ptr<VertexBuffer> m_VertexBuffer;//vbo
		std::unique_ptr<IndexBuffer> m_IndexBuffer;//ibo
		std::unique_ptr<Shader> m_Shader;


	private:
		static Application* s_Instance;
	};

	// to be define in client
	Application* CreateApplication();
}


