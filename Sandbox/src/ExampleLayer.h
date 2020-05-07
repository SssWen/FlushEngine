#pragma once


#include <Flush.h>

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Flush::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Flush::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Flush::Event& e) override;
private:
	Flush::ShaderLibrary m_ShaderLibrary;
	std::shared_ptr<Flush::VertexArray> m_VertexArray;// vao		
	Flush::Ref<Flush::Shader> m_Shader;

	std::shared_ptr<Flush::VertexArray> m_SquareVA;// vao				
	std::shared_ptr<Flush::Shader> m_FlatColorShader;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	Flush::Ref<Flush::Texture2D> m_Texture, m_AlphaTexture;
	Flush::OrthographicCameraController m_CameraController;
};