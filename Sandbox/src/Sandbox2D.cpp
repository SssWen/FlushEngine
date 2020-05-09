#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

//template<typename Fn>
//class Timer {
//public:
//	Timer(const char* name, Fn&& func) : m_Name(name), m_Func(func), m_Stopped(false) // Fn&& rvalue
//	{
//		m_StartTimepoint = std::chrono::high_resolution_clock::now();
//	}
//	~Timer()
//	{
//		if (!m_Stopped)
//			Stop();
//	}
//	void Stop()
//	{
//		auto endTimepoint = std::chrono::high_resolution_clock::now();
//
//		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
//		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
//
//		m_Stopped = true;
//
//		float duration = (end - start) * 0.001f;
//		m_Func({ m_Name, duration });
//	}
//private:
//	const char* m_Name;
//	Fn m_Func;
//	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
//	bool m_Stopped;
//};
//#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1) // 1280.0f / 720.0f
{
}

void Sandbox2D::OnAttach()
{
	//m_CheckerboardTexture = Flush::Texture2D::Create("assets/textures/Checkerboard.png");
	m_CheckerboardTexture = Flush::Texture2D::Create("assets/textures/Alphaboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Flush::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Flush::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Flush::RenderCommand::Clear();
	{
		// Draw Quad
		FLUSH_PROFILE_SCOPE("Draw Renderer");

		Flush::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Flush::Renderer2D::DrawQuad({ 0.5f, -0.3f }, { 0.8f, 0.8f }, { 1.0f, 0.2f, 0.3f, 1.0f });
		Flush::Renderer2D::DrawQuad({ 0.2f, -0.5f }, { 0.5f, 0.75f }, { 0.0f, 0.3f, 0.8f, 1.0f });
		//Flush::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		/*Flush::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Flush::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 20.0f);*/
		Flush::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 1.0f);
		Flush::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	//FLUSH_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	/*for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();*/	
	ImGui::End();	
}

void Sandbox2D::OnEvent(Flush::Event& e)
{
	m_CameraController.OnEvent(e);
}