#pragma once
#include <Dogo/Core.h>
#include "Events/Event.h"
namespace Dogo
{
	class DG_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnResizeNotify() {}
		inline virtual const std::string& GetName() const { return m_Name; }
	protected:
		std::string m_Name;
	};
}

