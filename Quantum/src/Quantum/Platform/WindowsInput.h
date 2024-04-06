#pragma once
#include"Quantum/Input.h"
namespace Quantum {
	class WindowsInput : public Input
	{
	protected :
		
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual bool isMouseButtonPressedImpl(int keycode) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
		virtual std::pair<float, float> getMousePositionImpl() override;
	};
}
