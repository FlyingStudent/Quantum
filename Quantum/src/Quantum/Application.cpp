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
	Application::Application()
	{
		QT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
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
			glClearColor(1, 0, 1, 1); 
			glClear(GL_COLOR_BUFFER_BIT);
		
			for (Layer* layer : m_LayerStack)
			{
				layer->onUpdate();
			}
			
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
