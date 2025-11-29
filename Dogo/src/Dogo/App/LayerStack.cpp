#include "dgpch.h"
#include "LayerStack.h"

namespace Dogo {
	LayerStack::LayerStack()
	{
		// No need to initialize m_LayerInsert here.
	}

	LayerStack::~LayerStack()
	{
		// Delete each layer to avoid memory leaks
		for (Layer2D* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer2D* layer)
	{
		// Simply push the layer to the back of the vector
		m_Layers.push_back(layer);
	}

	void LayerStack::PushOverlay(Layer2D* overlay)
	{
		// Overlays are pushed to the end of the vector
		m_Layers.push_back(overlay);
	}

	void LayerStack::PopLayer(Layer2D* layer)
	{
		// Find the layer in the stack and erase it
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			// Once found, erase it from the stack
			m_Layers.erase(it);
		}
	}

	void LayerStack::PopOverlay(Layer2D* overlay)
	{
		// Find and erase overlay in the stack
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}
