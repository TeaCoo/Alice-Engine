#pragma once
#include "Alice/Core.h"
#include "Alice/Layer/Layer.h"
#include "Alice/Event/KeyEvent.h"
#include "Alice/Event/MouseEvent.h"
#include "Alice/Event/ApplicationEvent.h"

namespace Alice 
{
	class ALICE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}


