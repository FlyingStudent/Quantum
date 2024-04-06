#include<Quantum.h>
#include<iostream>
#include<glm.hpp>
class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{ }
	void onUpdate() override
	{
		QT_CLIENT_INFO("ExampleLayer::Update");
		if(Quantum::Input::isKeyPressed(QT_KEY_TAB))
		QT_CLIENT_INFO("Tab Key is pressed!");
		glm::vec2 vec = glm::vec2(0.0f);
		QT_CLIENT_TRACE("{0}", vec[0]);
	}
	void onEvent(Quantum::Event& event) override
	{
		QT_CLIENT_TRACE(event.toString());
	}
};
class sandBoxApp: public Quantum::Application
{
public:
	sandBoxApp()
	{
		pushLayer(new ExampleLayer());
		pushOverlay(new Quantum::ImGuiLayer());
	}
	~sandBoxApp()
	{

	}

};

//entry point function implementation
Quantum::Application* createApplication()
{

	return new sandBoxApp();
}