#pragma once

#include "Flush/Core.h"
#include "Flush/Events/Event.h"

namespace Flush 
{
	class FLUSH_API Layer 
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual	~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:

		std::string m_DebugName;

	};
}