#pragma once
#include "Alice/ImGui/ImGuiLayer.h"
#include "Alice/GUI/Mesh_Debug_GUI.h"
namespace Alice {
	class ALICE_API Mash_Debug : public ImGuiLayer
	{
	public:
		Mash_Debug();
		~Mash_Debug();
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
	private:
		Mesh_Debug_GUI* mesh_gui_ptr;

	private: // test !!!!! need to remove
		unsigned int index_count;
		unsigned int id;
		unsigned int index;
		
		bool drawline = true;
	};
}

