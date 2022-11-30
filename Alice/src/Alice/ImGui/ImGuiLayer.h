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
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleaseEvent(KeyReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMousePressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseMovedEvent(MouseMoveEvent& e);
		bool OnMouseReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyTypeEvent(KeyTypedEvent& e);
		void MapGLFWKey();
	private:
		float m_Time = 0.0f;
	};
}


