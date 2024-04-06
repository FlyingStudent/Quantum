#include"qtpch.h"
#include "WindowsInput.h"
#include<GLFW/glfw3.h> 
#include"Quantum/Application.h"
namespace Quantum {
		Input* Input::s_Instance = new WindowsInput(); 
	bool Quantum::WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
			int state = glfwGetKey(window, keycode);
			return state == GLFW_PRESS || GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;

	}

float WindowsInput::getMouseXImpl()
	{
	auto [x, y] = getMousePositionImpl();
	return (float)x;
	}
	float WindowsInput::getMouseYImpl()
	{
		auto [x, y] = getMousePositionImpl();
		return (float)y;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl() 
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos,(float)ypos };
	}

}