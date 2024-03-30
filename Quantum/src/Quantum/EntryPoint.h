#pragma once
#include"Application.h"
#include"Log.h"
#ifdef QT_PLATFORM_WINDOWS
extern Quantum::Application* createApplication();
int  main(int argc, char** argv)
{
	Quantum::Log::init();
	QT_CORE_WARN("Initialized Core Logger!");
	int a = 5;
	QT_CLIENT_INFO("Initialized Client Logger! Var={0}",a);
	auto app = createApplication();
	delete app;
	return 0;
}
#endif
