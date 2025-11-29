#pragma once
#include <Dogo/Core.h>
#include "Layer.h"
namespace Dogo
{
	class DG_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer2D* layer);
		void PushOverlay(Layer2D* overlay);
		void PopLayer(Layer2D* layer);
		void PopOverlay(Layer2D* overlay);

		std::vector<Layer2D*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer2D*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer2D*> m_Layers;
		//std::vector<Layer*>::iterator m_LayerInsert;
	};
}

