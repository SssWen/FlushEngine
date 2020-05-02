#include "flushpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "glad/glad.h"
#include "Flush/Input.h"
#include "Flush/Renderer/Renderer.h"


namespace Flush {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Flush::ShaderDataType::Float:    return GL_FLOAT;
		case Flush::ShaderDataType::Float2:   return GL_FLOAT;
		case Flush::ShaderDataType::Float3:   return GL_FLOAT;
		case Flush::ShaderDataType::Float4:   return GL_FLOAT;
		case Flush::ShaderDataType::Mat3:     return GL_FLOAT;
		case Flush::ShaderDataType::Mat4:     return GL_FLOAT;
		case Flush::ShaderDataType::Int:      return GL_INT;
		case Flush::ShaderDataType::Int2:     return GL_INT;
		case Flush::ShaderDataType::Int3:     return GL_INT;
		case Flush::ShaderDataType::Int4:     return GL_INT;
		case Flush::ShaderDataType::Bool:     return GL_BOOL;
		}

		//FLUSH_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		//HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer(); // 创建一个GUI 
		PushOverlay(m_ImGuiLayer);
		

#pragma region ---------------create vao---------------

		/*glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);*/

		m_VertexArray.reset(VertexArray::Create());
			
		float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
#pragma endregion 		
#pragma region ---------------create vbo---------------

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		
#pragma endregion 
#pragma region ---------------create ibo---------------						
		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

#pragma endregion 	
#pragma region ---------------create shader obj---------------		
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
#pragma endregion 

	//  Create Square 
#pragma region ---------------create vao---------------
		m_SquareVA.reset(VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
#pragma endregion 	
#pragma region ---------------create vbo---------------
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);
#pragma endregion

#pragma region ---------------create ibo---------------
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);
#pragma endregion
#pragma region ---------------create shader---------------
		
		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
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

		m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
#pragma endregion
	}
	Application::~Application()
	{

	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//Flush_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{			
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

#pragma region --------Update Mesh-------------
			// 重构 refractor
			// draw square 
			Renderer::BeginScene();
			m_BlueShader->Bind();
			Renderer::Submit(m_SquareVA);
			// draw triangle
			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();
#pragma endregion

#pragma region --------Update UI-------------
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// draw gui
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender(); // ShowDemoWindow
			m_ImGuiLayer->End();
#pragma endregion

			m_Window->OnUpdate();

		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}