#include<Quantum.h>
#include<iostream>
class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{ }
	void onUpdate() override
	{
		QT_CLIENT_INFO("ExampleLayer::Update");
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