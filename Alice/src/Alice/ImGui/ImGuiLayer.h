#pragma once
#include "Alice/Core.h"
#include "Alice/Layer/Layer.h"
namespace Alice 
{
	class ALICE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
	};
}


