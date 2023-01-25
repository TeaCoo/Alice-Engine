#pragma once

namespace Alice {
	class ALICE_API Mesh_Debug_GUI
	{
	public: 
		void MeshGUI(bool* p_open);
		void ShowGUI(bool* p_open);
		std::string TCHARTurnString(TCHAR* STR);
		LPCWSTR stringToLPCWSTR(std::string orig);

	public:
		bool drawline = true;
	private:
		std::string Path = "";
	};
}

