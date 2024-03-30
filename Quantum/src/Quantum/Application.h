#pragma once
#include"Core.h"
namespace Quantum {

	class QUANTUM_API Application
	{
	public:
		Application();
		virtual ~Application();
		void print();
		//to be implemented by user
		Application* createApplication();
		void run();
	};
}

