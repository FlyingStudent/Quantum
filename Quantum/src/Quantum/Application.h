#pragma once
#include"Core.h"
#include"Events/Event.h"
#include"Events/ApplicationEvent.h"
#include"Window.h"
#include"LayerStack.h"
#include"Input.h"
#include"Quantum/ImGui/ImGuiLayer.h"
#include"Quantum/Renderer/Shader.h"
#include"Quantum/Renderer/Buffer.h"
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
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		unsigned int m_VertexArray;

	private:

		static Application* s_Instance;
	};
	// to be defined in client
	Application* createApplication();
}

