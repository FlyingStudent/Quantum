#pragma once
#include"Quantum/Window.h"
struct GLFWwindow;
namespace Quantum {

	class WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		
		virtual ~WindowsWindow() ;
		
		void onUpdate() override;
		inline unsigned int getWidth() const override { return m_Data.width; }
		inline unsigned int getHeight() const override { return m_Data.height; }

		//Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override {
			m_Data.EventCallback = callback;
		}
		void setVSync(bool enabled)override;
		bool IsVSync() const override ;
	private:
		virtual void init(const WindowProps& props);
		virtual void shutDown();
	private:
		GLFWwindow* m_Window;
		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}