#pragma once

#ifdef ALICE_PLATFORM_WINDOWS

extern Alice::Application* Alice::CreateApplication();

int main(int argc, char** argv) {
	printf("Alice Engine is running!\n");

	Alice::Log::Init();
	ALICE_CORE_WARN("Initialized Log!");
	ALICE_INFO("Hello!");

	auto app = Alice::CreateApplication();

	app->Run();
	delete app;
}

#endif // ALICE_PLATFORM_WINDOWS

