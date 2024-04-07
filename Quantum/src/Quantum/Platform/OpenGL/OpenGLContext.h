#pragma once
#include"Quantum/Renderer/GraphicsContext.h"
struct GLFWwindow;
namespace Quantum {
	class OpenGLContext : public GraphicsContext{
		public:
			OpenGLContext(GLFWwindow* windowHandle);
			virtual void init() override;
			virtual void swapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
