#pragma once
#include "Alice/ImGui/ImGuiLayer.h"
#include "Alice/GUI/mainGUI.h"

namespace Alice {
	class ALICE_API ImGui_Engine_Editer : public ImGuiLayer
	{
	public:
		ImGui_Engine_Editer();
		~ImGui_Engine_Editer();
		virtual void OnImGuiRender() override;
	private:
		mainGUI* main_gui_ptr;
	};
}
