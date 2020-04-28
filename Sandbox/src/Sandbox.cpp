
#include <Flush.h>
class ExampleLayer : public Flush::Layer 
{
public:
	ExampleLayer() : Layer("Example")
	{		
	}

	void OnUpdate() override
	{
		//Flush_ERROR("ExampleLayer::Update");
		if (Flush::Input::IsKeyPressed(F_KEY_TAB))
		{
			Flush_TRACE("Tab key is pressed(poll)!");;
		}
	}

	void OnEvent(Flush::Event& event) override 
	{		
		if (event.GetEventType() == Flush::EventType::KeyPressed)
		{
			Flush::KeyPressedEvent& e = (Flush::KeyPressedEvent&)event;
			if (e.GetKeyCode() == F_KEY_TAB)
				Flush_TRACE("Tab key is pressed (event)!");
			Flush_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Flush::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		//PushLayer(new Flush::ImGuiLayer());
	}
	~Sandbox() {

	}
};

Flush::Application* Flush::CreateApplication()
{
	return new Sandbox();
}