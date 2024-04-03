#pragma once
#include"qtpch.h"
#include"Quantum/Core.h"
#include"Quantum/Events/Event.h"
namespace Quantum {
	struct WindowProps {
		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
		WindowProps(const std::string& title = "Quantum Engine",
			unsigned int width = 640,
			unsigned int height = 480)
			:m_Title(title),m_Width(width),m_Height(height){}
	};

//Interface representing a desktop system based Window
	class QUANTUM_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}
		virtual void onUpdate() = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		//Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		static Window* create(const WindowProps& props = WindowProps());

	};
}