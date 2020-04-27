
#include <Flush.h>

class ExampleLayer : public Flush::Layer 
{
public:
	ExampleLayer() : Layer("Example")
	{

	}

	void OnUpdate() override
	{
		Flush_ERROR("ExampleLayer::Update");
	}

	void OnEvent(Flush::Event& event) override 
	{
		Flush_WARN("{0}", event);
	}

};

class Sandbox : public Flush::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushLayer(new Flush::ImGuiLayer());
	}
	~Sandbox() {

	}
};

Flush::Application* Flush::CreateApplication()
{
	return new Sandbox();
}