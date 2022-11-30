git submodule add https://github.com/TeaCoo/glfw.git Alice/extern/GLFW
git submodule add https://github.com/TeaCoo/imgui.git Alice/extern/imgui
git submodule add https://github.com/gabime/spdlog.git Alice/extern/spdlog

call extern\bin\premake\premake5.exe vs2019
PAUSE
