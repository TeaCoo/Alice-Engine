#include "pch.h"
#include "imgui.h"
#include "Mesh_Debug_GUI.h"
namespace Alice
{
	void Mesh_Debug_GUI::MeshGUI(bool* p_open)
	{
        if (!ImGui::Begin("Mesh Debug", p_open))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }

        // Most "big" widgets share a common width settings by default. See 'Demo->Layout->Widgets Width' for details.
        // e.g. Use 2/3 of the space for widgets and 1/3 for labels (right align)
        //ImGui::PushItemWidth(-ImGui::GetWindowWidth() * 0.35f);
        // e.g. Leave a fixed amount of width for labels (by passing a negative value), the rest goes to widgets.
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

        // The input path of object        
		ImGui::Text("Object path:");
		ImGui::SameLine();
		static char path[MAX_PATH] = "";
		strcpy(path, this->Path.data());
		ImGui::InputText(" ", path, IM_ARRAYSIZE(path));
		this->Path = path;

		ImGui::SameLine();
		if (ImGui::Button("File")) {
			std::string text = "something";
			wchar_t wtext[20];
			mbstowcs(wtext, text.c_str(), text.length());//includes null
			LPWSTR szFile = wtext;

			OPENFILENAME ofn;
			
			// open a file name
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = stringToLPCWSTR("All\0*.*\0Text\0*.TXT\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			GetOpenFileName(&ofn);
		}

		ImGui::Checkbox("Draw wireframe", &drawline);
        // End of ShowDemoWindow()
        ImGui::PopItemWidth();
        ImGui::End();
	}

	void Alice::Mesh_Debug_GUI::ShowGUI(bool* p_open)
	{
		IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");
		MeshGUI(p_open);
	}

	std::string Alice::Mesh_Debug_GUI::TCHARTurnString(TCHAR* STR)
	{
		int iLen = WideCharToMultiByte(CP_ACP, 0, STR, -1, NULL, 0, NULL, NULL);
		char* chRtn = new char[iLen * sizeof(char)];
		WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
		std::string str(chRtn);
		return str;
	}

	LPCWSTR Alice::Mesh_Debug_GUI::stringToLPCWSTR(std::string orig)
	{
		size_t origsize = orig.length() + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
		mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

		return wcstring;
	}
}