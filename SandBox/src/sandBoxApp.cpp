#include<Quantum.h>
#include<iostream>
class sandBoxApp: public Quantum::Application
{
public:
	sandBoxApp()
	{

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