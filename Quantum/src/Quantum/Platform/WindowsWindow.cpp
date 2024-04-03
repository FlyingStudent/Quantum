#include"qtpch.h"
#include"WindowsWindow.h"
#include"Quantum/Events/ApplicationEvent.h"
#include"Quantum/Events/KeyEvent.h"
#include"Quantum/Events/MouseEvent.h"
#include<GLFW/glfw3.h>
#include<glad\glad.h>
namespace Quantum {
	static bool s_GLFWInitialized = false;
	static void  GLFWErrorCallback(int error, const char* description)
	{
		QT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}
	Window* Window::create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		shutDown();
	}
	void WindowsWindow::init(const WindowProps& props)
	{
		m_Data.title = props.m_Title;
		m_Data.width = props.m_Width;
		m_Data.height = props.m_Height;
		QT_CORE_INFO("Creatig Window {0} ({1} , {2})", props.m_Title, props.m_Width, props.m_Height);

	if (!s_GLFWInitialized)
	{
		//ToDo: glfwTerminate on system shutdown
		glfwSetErrorCallback([](int  error, const char* description) {
			std::cout << "Error: " << error << ", description: " << description << std::endl;
			});
		int success = glfwInit();
		QT_CORE_ASSERT(success, "Could not initialize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		s_GLFWInitialized = true;
	}
	m_Window = glfwCreateWindow((int)props.m_Width, (int)props.m_Height, m_Data.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	int status = gladLoadGLLoader((GLADloadproc )glfwGetProcAddress);
	QT_CORE_ASSERT(status, "FAiled to initialize GLAD ");
	glfwSetWindowUserPointer(m_Window, &m_Data);
	setVSync(true);
	//set glfw callbacks
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowResizeEvent event(width, height);
		data.width = width;
		data.height = height;
		data.EventCallback(event);
		glViewport(0, 0, width, height);
		});
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallback(event);
		});
	glfwSetKeyCallback(m_Window, [](GLFWwindow* window,int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent event(key, 0);
			data.EventCallback(event);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent event(key);
			data.EventCallback(event);
			break;
		}
		case GLFW_REPEAT:
			KeyPressedEvent event(key, 1);
			data.EventCallback(event);
			break;
		}
		
		});
	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}

			}
		});
	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);

		});
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		KeyTypedEvent event(keycode);
		data.EventCallback(event);
		});
	}
	void WindowsWindow::shutDown()
	{
		glfwDestroyWindow(m_Window);
	}
	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}