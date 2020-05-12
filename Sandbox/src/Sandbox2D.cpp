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
	// Renderer::Init();在Application上
}

void Sandbox2D::OnAttach()
{
	//m_CheckerboardTexture = Flush::Texture2D::Create("assets/textures/Checkerboard.png");
	m_CheckerboardTexture = Flush::Texture2D::Create("assets/textures/Alphaboard.png");

	// Init here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Flush::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// 每帧执行前 清空 stats 数据
	Flush::Renderer2D::ResetStats();
	// Render
	Flush::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Flush::RenderCommand::Clear();

	{		
		FLUSH_PROFILE_SCOPE("Draw Renderer");

		// DrawCall = 1
		Flush::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Flush::Renderer2D::DrawQuad({ 0.5f, -0.3f }, { 0.8f, 0.8f }, { 1.0f, 0.2f, 0.3f, 1.0f });
		Flush::Renderer2D::DrawQuad({ 0.2f, -0.5f }, { 0.5f, 0.75f }, { 0.0f, 0.3f, 0.8f, 1.0f });
		//Flush::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		/*Flush::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Flush::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 20.0f);*/
		Flush::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 1.0f);
		Flush::Renderer2D::EndScene();


		// DrawCall = 2
		Flush::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Flush::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Flush::Renderer2D::EndScene();
	}

	// ParticleSystem DrawCall = 3

	if (Flush::Input::IsMouseButtonPressed(F_MOUSE_BUTTON_LEFT))
	{
		auto[x, y] = Flush::Input::GetMousePosition();
		auto width = Flush::Application::Get().GetWindow().GetWidth();
		auto height = Flush::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_ParticleSystem.Emit(m_Particle);
	}

	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

}

void Sandbox2D::OnImGuiRender()
{
	
	ImGui::Begin("Settings");

	auto stats = Flush::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}


void Sandbox2D::OnEvent(Flush::Event& e)
{
	m_CameraController.OnEvent(e);
}