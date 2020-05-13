#pragma once

#include <Flush.h>
#include "ParticleSystem.h""

class Sandbox2D : public Flush::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Flush::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Flush::Event& e) override;
private:
	Flush::OrthographicCameraController m_CameraController;

	// Temp
	Flush::Ref<Flush::VertexArray> m_SquareVA;
	Flush::Ref<Flush::Shader> m_FlatColorShader;
	Flush::Ref<Flush::Texture2D> m_CheckerboardTexture;
	Flush::Ref<Flush::Texture2D> m_SpriteTexture;
	Flush::Ref<Flush::SubTexture2D> m_SubTexture, m_SubTexture1, m_SubTexture2;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;

	//struct ProfileResult
	//{
	//	const char* Name;
	//	float Time;
	//};
	//std::vector<ProfileResult> m_ProfileResults;
};