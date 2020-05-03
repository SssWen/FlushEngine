
#include <Flush.h>
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Flush::Layer 
{

public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{	
		// Create Triangle
#pragma region ---------------create vao---------------

		/*glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);*/

		m_VertexArray.reset(Flush::VertexArray::Create());


#pragma endregion 		
#pragma region ---------------create vbo---------------

		float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Flush::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Flush::VertexBuffer::Create(vertices, sizeof(vertices)));
		Flush::BufferLayout layout = {
				{ Flush::ShaderDataType::Float3, "a_Position" },
				{ Flush::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

#pragma endregion 
#pragma region ---------------create ibo---------------						
		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Flush::IndexBuffer> indexBuffer;
		indexBuffer.reset(Flush::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

#pragma endregion 	
#pragma region ---------------create shader obj---------------		
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection *u_Transform* vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Flush::Shader(vertexSrc, fragmentSrc));


#pragma endregion 

		//  Create Square 
#pragma region ---------------create vao---------------
		m_SquareVA.reset(Flush::VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
#pragma endregion 	
#pragma region ---------------create vbo---------------
		std::shared_ptr<Flush::VertexBuffer> squareVB;
		squareVB.reset(Flush::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Flush::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);
#pragma endregion

#pragma region ---------------create ibo---------------
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Flush::IndexBuffer> squareIB;
		squareIB.reset(Flush::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);
#pragma endregion
#pragma region ---------------create shader---------------
		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Flush::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));


#pragma endregion
	}

	void OnUpdate(Flush::Timestep ts) override
	{		
		// key
		if (Flush::Input::IsKeyPressed(F_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Flush::Input::IsKeyPressed(F_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Flush::Input::IsKeyPressed(F_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Flush::Input::IsKeyPressed(F_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Flush::Input::IsKeyPressed(F_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Flush::Input::IsKeyPressed(F_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		

		Flush::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flush::RenderCommand::Clear();

#pragma region --------Update Mesh-------------
		// ÷ÿππ refractor
		// draw square 
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		Flush::Renderer::BeginScene(m_Camera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Flush::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}		
		// draw triangle			
		Flush::Renderer::Submit(m_Shader, m_VertexArray);
		Flush::Renderer::EndScene();


#pragma endregion
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

	virtual void OnImGuiRender() override
	{

	}

private:
	std::shared_ptr<Flush::VertexArray> m_VertexArray;// vao		
	std::shared_ptr<Flush::Shader> m_Shader;

	std::shared_ptr<Flush::VertexArray> m_SquareVA;// vao				
	std::shared_ptr<Flush::Shader> m_BlueShader;
	Flush::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

};

class Sandbox : public Flush::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());				
	}
	~Sandbox() {

	}
};

Flush::Application* Flush::CreateApplication()
{
	return new Sandbox();
}