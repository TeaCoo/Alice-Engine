#include "pch.h"
#include "imgui.h"
#include "mainGUI.h"
namespace Alice
{
    void mainGUI::ShowAppMainMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ShowMenuFile();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Windows"))
            {
                if (ImGui::MenuItem("Hierachy", NULL, &(this->show_app_hierachy))) {}
                if (ImGui::MenuItem("Project", NULL, &(this->show_app_project))) {}
                if (ImGui::MenuItem("Game", NULL, &(this->show_app_game))) {}
                if (ImGui::MenuItem("Inspector", NULL, &(this->show_app_inspector))) {}
                if (ImGui::MenuItem("Scene", NULL, &(this->show_app_scene))) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void mainGUI::ShowMenuFile()
    {
        ImGui::MenuItem("(demo menu)", NULL, false, false);
        if (ImGui::MenuItem("New")) {}
        if (ImGui::MenuItem("Open", "Ctrl+O")) {}
        if (ImGui::BeginMenu("Open Recent"))
        {
            ImGui::MenuItem("fish_hat.c");
            ImGui::MenuItem("fish_hat.inl");
            ImGui::MenuItem("fish_hat.h");
            if (ImGui::BeginMenu("More.."))
            {
                ImGui::MenuItem("Hello");
                ImGui::MenuItem("Sailor");
                if (ImGui::BeginMenu("Recurse.."))
                {
                    ShowMenuFile();
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Save", "Ctrl+S")) {}
        if (ImGui::MenuItem("Save As..")) {}

        ImGui::Separator();
        if (ImGui::BeginMenu("Options"))
        {
            static bool enabled = true;
            ImGui::MenuItem("Enabled", "", &enabled);
            ImGui::BeginChild("child", ImVec2(0, 60), true);
            for (int i = 0; i < 10; i++)
                ImGui::Text("Scrolling Text %d", i);
            ImGui::EndChild();
            static float f = 0.5f;
            static int n = 0;
            ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
            ImGui::InputFloat("Input", &f, 0.1f);
            ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Colors"))
        {
            float sz = ImGui::GetTextLineHeight();
            for (int i = 0; i < ImGuiCol_COUNT; i++)
            {
                const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
                ImVec2 p = ImGui::GetCursorScreenPos();
                ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
                ImGui::Dummy(ImVec2(sz, sz));
                ImGui::SameLine();
                ImGui::MenuItem(name);
            }
            ImGui::EndMenu();
        }

        // Here we demonstrate appending again to the "Options" menu (which we already created above)
        // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
        // In a real code-base using it would make senses to use this feature from very different code locations.
        if (ImGui::BeginMenu("Options")) // <-- Append!
        {
            static bool b = true;
            ImGui::Checkbox("SomeOption", &b);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Disabled", false)) // Disabled
        {
            IM_ASSERT(0);
        }
        if (ImGui::MenuItem("Checked", NULL, true)) {}
        if (ImGui::MenuItem("Quit", "Alt+F4")) {}
    }

    void mainGUI::ShowDockingDisabledMessage()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
        ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
        ImGui::SameLine(0.0f, 0.0f);
        if (ImGui::SmallButton("click here"))
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    }

    void mainGUI::ShowAppDockSpace(bool* p_open)
    {
        // If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
        // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
        // In this specific demo, we are not using DockSpaceOverViewport() because:
        // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
        // - we allow the host window to have padding (when opt_padding == true)
        // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
        // TL;DR; this demo is more complicated than what you would normally use.
        // If we removed all the options we are showcasing, this demo would become:
        //     void ShowExampleAppDockSpace()
        //     {
        //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        //     }

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Main DockSpace", p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("AliceDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            ShowDockingDisabledMessage();
        }

        ImGui::End();
    }

    void mainGUI::ShowAppInspector(bool* p_open)
    {
        if (!ImGui::Begin("Inspector", p_open))
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

        // End of ShowDemoWindow()
        ImGui::PopItemWidth();
        ImGui::End();
    }

    void mainGUI::ShowAppGameWindow(bool* p_open)
    {
        if (!ImGui::Begin("Game", p_open))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

        // End of ShowDemoWindow()
        ImGui::PopItemWidth();
        ImGui::End();
    }

    void mainGUI::ShowAppProject(bool* p_open)
    {
        if (!ImGui::Begin("Project", p_open))
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

        // End of ShowDemoWindow()
        ImGui::PopItemWidth();
        ImGui::End();
    }

    void mainGUI::ShowAppHierachy(bool* p_open)
    {
        // Main body of the Demo window starts here.
        if (!ImGui::Begin("Hierachy", p_open))
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

        // End of ShowDemoWindow()
        ImGui::PopItemWidth();
        ImGui::End();
    }

    void mainGUI::ShowAppScene(bool* p_open)
    {
        if (!ImGui::Begin("Scene", p_open))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return;
        }
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

        // End of ShowDemoWindow()
        ImGui::PopItemWidth();
        ImGui::End();
    }

    void mainGUI::showMainGUI(bool* p_open)
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");

        if (this->show_app_main_menu_bar)     ShowAppMainMenuBar();
        if (this->show_app_dockspace)         ShowAppDockSpace(&(this->show_app_dockspace));
        if (this->show_app_scene)             ShowAppScene(&(this->show_app_scene));
        if (this->show_app_hierachy)          ShowAppHierachy(&(this->show_app_hierachy));
        if (this->show_app_project)           ShowAppProject(&(this->show_app_project));
        if (this->show_app_game)              ShowAppGameWindow(&(this->show_app_game));
        if (this->show_app_inspector)         ShowAppInspector(&(this->show_app_inspector));


        // Demonstrate the various window flags. Typically you would just use the default!
        static bool no_titlebar = false;
        static bool no_scrollbar = false;
        static bool no_menu = false;
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = false;
        static bool no_close = true;
        static bool no_nav = false;
        static bool no_background = false;
        static bool no_bring_to_front = false;
        static bool no_docking = false;
        static bool unsaved_document = false;

        ImGuiWindowFlags window_flags = 0;

        if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
        if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
        if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
        if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
        if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
        if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
        if (no_close)           p_open = NULL; // Don't pass our bool* to Begin


        // We specify a default position/size in case there's no data in the .ini file.
        // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
        //const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        //ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        //ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    }
}