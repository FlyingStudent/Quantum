#pragma once
#include"Quantum/Core.h"
#include"Layer.h"
#include<vector>
namespace Quantum {
	class QUANTUM_API LayerStack {
	public :
		LayerStack();
		~LayerStack();
		
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlaye);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }

		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}