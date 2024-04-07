#include<qtpch.h>
#include"OpenGLContext.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
namespace Quantum {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		QT_CORE_ASSERT(m_WindowHandle, "Window Handle is null!");
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QT_CORE_ASSERT(status, "FAiled to initialize GLAD ");
		QT_CORE_INFO("OpenGL Info: ");
		QT_CORE_INFO("  Vendor: {0}", static_cast<std::string>(reinterpret_cast<const char*> (glGetString(GL_VENDOR))));
		QT_CORE_INFO("  Renderer: {0}", static_cast<std::string>(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
		QT_CORE_INFO("  Version: {0}", static_cast<std::string>(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
	}
	void OpenGLContext::swapBuffers()
	{
		
		glfwSwapBuffers(m_WindowHandle);
	}
}