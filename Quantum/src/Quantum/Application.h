#pragma once
#include"Core.h"
#include"Events/Event.h"
#include"Events/ApplicationEvent.h"
#include"Window.h"
#include"LayerStack.h"
namespace Quantum {

	class QUANTUM_API Application
	{
	public:
		Application();
		virtual ~Application();
		void print();
		void run();
		void onEvent(Event& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		inline Window& getWindow() const { return *m_Window; }
		inline static Application& get() {
			return *s_Instance;
		}
	private:
		bool onWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
	};
	// to be defined in client
	Application* createApplication();
}

