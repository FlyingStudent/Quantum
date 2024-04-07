#include"qtpch.h"
#include"Events/ApplicationEvent.h"
#include"Events/Event.h"
#include"Log.h"
#include<iostream>
#include"Application.h"
#include<glad/glad.h>
namespace Quantum {
Application* Application::s_Instance = nullptr;
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
	case Quantum::ShaderDataType::Float: return GL_FLOAT;
	case Quantum::ShaderDataType::Float2: return GL_FLOAT;
	case Quantum::ShaderDataType::Float3: return GL_FLOAT;
	case Quantum::ShaderDataType::Float4: return GL_FLOAT;
	case Quantum::ShaderDataType::Int: return GL_INT;
	case Quantum::ShaderDataType::Int2: return GL_INT;
	case Quantum::ShaderDataType::Int3: return GL_INT;
	case Quantum::ShaderDataType::Int4: return GL_INT;
	case Quantum::ShaderDataType::Mat3: return GL_FLOAT;
	case Quantum::ShaderDataType::Mat4: return GL_FLOAT;
	case Quantum::ShaderDataType::Bool: return GL_BOOL;
}
	QT_CORE_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}
	Application::Application()
	{
		QT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::create());
		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);
		m_Window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] =
		{
			/* position*/		/*color*/
			-0.5f,-0.5f,0.0f,	0.8f,0.2f,0.8f,1.0f,
			0.5f,-0.5f,0.0f,	0.2f,0.3f,0.8f,1.0f,
			0.0f,0.5f,0.0f,		0.8f,0.8f,0.2f,1.0f
		};
		m_VertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ShaderDataType::Float4, "a_Color"}
		 };
		m_VertexBuffer->setLayout(layout);
		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->getLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.getComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE,m_VertexBuffer->getLayout().getStride(), (const void*)element.Offset);
			index++;
		}
		uint32_t indecies[] = 
		{
			0,1,2

		};
		m_IndexBuffer.reset(IndexBuffer::create(indecies, sizeof(indecies) / sizeof(uint32_t)));
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location =1 ) in vec4 a_Color;

out vec3 v_Position;
out vec4 v_Color;

void main()
{

v_Position = a_Position;
v_Color = a_Color;
gl_Position = vec4(a_Position,1.0);

}

)";
		std::string fragmentSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
void main()
{

color = v_Color;

}

)";

		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));
		m_Shader->bind();
	}
	 Application::~Application() {

	}
	void  Application::print()
	{
		std::cout << "Welcome to Quantum Engine!" << std::endl;
	}
	void Application::run()
	{
	//	WindowResizeEvent e(640, 480);
	//	QT_CORE_TRACE(e);
		while (m_Running)
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1); 
			glClear(GL_COLOR_BUFFER_BIT);
	
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
			{
				layer->onUpdate();
			}
			
			auto [x, y] = Input::getMousePosition();
			QT_CORE_TRACE("{0}, {1}", x, y);
			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();
			m_Window->onUpdate();
		 
		
		}
	}
	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
		QT_CORE_TRACE(e.toString());
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.isHandled())
				break;
		}





	}
	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	void Application::pushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* overlay)
	{
		m_LayerStack.pushOverlay(overlay);
		overlay->onAttach();
	}
}
