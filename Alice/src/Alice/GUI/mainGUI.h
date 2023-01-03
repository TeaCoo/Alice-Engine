#pragma once
namespace Alice
{
	class mainGUI
	{
	public:
		void showMainGUI(bool* p_open);
		void ShowAppMainMenuBar();
		void ShowMenuFile();
		void ShowDockingDisabledMessage();
		void ShowAppDockSpace(bool* p_open);
		void ShowAppInspector(bool* p_open);
		void ShowAppGameWindow(bool* p_open);
		void ShowAppProject(bool* p_open);
		void ShowAppHierachy(bool* p_open);
		void ShowAppScene(bool* p_open);

	private:
		bool show_app_main_menu_bar = true;
		bool show_app_dockspace = true;
		bool show_app_scene = false;
		bool show_app_hierachy = true;
		bool show_app_project = true;
		bool show_app_game = false;
		bool show_app_inspector = true;
	};
}
