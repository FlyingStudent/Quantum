#pragma once
#include"Quantum/Layer.h"
#include"Quantum/Events/Event.h"
#include"Quantum/Events/KeyEvent.h"
#include"Quantum/Events/MouseEvent.h"
#include"Quantum/Events/ApplicationEvent.h"
namespace Quantum {
	class QUANTUM_API ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override ;
		virtual void onDetach() override ;
		//virtual void onUpdate() override;
		virtual void onImGuiRender() override;
		void begin();
		void end();
		/*void onEvent(Event& event);
	private:
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool  onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);*/

	private:
		float m_Time = 0.0f;

	};
}