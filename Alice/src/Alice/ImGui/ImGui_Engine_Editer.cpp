#include "pch.h"
#include "ImGui_Engine_Editer.h"

Alice::ImGui_Engine_Editer::ImGui_Engine_Editer()
{
	this->main_gui_ptr = new mainGUI();
}

Alice::ImGui_Engine_Editer::~ImGui_Engine_Editer()
{
	delete this->main_gui_ptr;
}

void Alice::ImGui_Engine_Editer::OnImGuiRender()
{
	static bool show = true;
	//ImGui::ShowDemoWindow(&show);
	this->main_gui_ptr->showMainGUI(&show);
}
