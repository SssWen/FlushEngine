#pragma once

#include "Flush/Layer.h"
#include "Flush/Events/MouseEvent.h"
#include "Flush/Events/KeyEvent.h"
#include "Flush/Events/ApplicationEvent.h"

namespace Flush {

	class FLUSH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		//void OnUpdate();
		//void OnEvent(Event& event);

		void OnImGuiRender();
		void Begin();
		void End();
	private:
		/*bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);*/
	private:
		float m_Time = 0.0f;
	};

}