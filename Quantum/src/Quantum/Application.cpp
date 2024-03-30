#include "Application.h"
#include"Events/ApplicationEvent.h"
#include"Log.h"
#include<iostream>
namespace Quantum {
	Application::Application()
	{

	}
	 Application::~Application() {

	}
	void  Application::print()
	{
		std::cout << "Welcome to Quantum Engine!" << std::endl;
	}
	void Application::run()
	{
		WindowResizeEvent e(640, 480);
		QT_CORE_TRACE(e);
		while (true);
	}
}