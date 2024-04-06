#pragma once
#include"Quantum/Core.h"
namespace Quantum {
	class QUANTUM_API Input {
	public :
	inline	static bool isKeyPressed(int keycode) {
			return s_Instance->isKeyPressedImpl(keycode);
		}	
	inline	static bool isMouseButtonPressed(int button) {
			return s_Instance->isMouseButtonPressedImpl(button);
		}
	inline	static bool getMouseY() {
			return s_Instance->getMouseYImpl();
		}
	inline	static bool getMouseX() {
			return s_Instance->getMouseXImpl();
		}
	inline	static std::pair<float,float> getMousePosition() {
			return s_Instance->getMousePositionImpl();
		}


	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float,float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}