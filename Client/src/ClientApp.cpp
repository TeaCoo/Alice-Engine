#include <Alice.h>
#include "Alice/ImGui/ImGuiLayer.h"
class ExampleLayer :public Alice::Layer 
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//ALICE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Alice::Event& event) override
	{
		//ALICE_TRACE("{0}", event);
	}
};

class Client : public Alice::Application {
public: 
	Client() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Alice::ImGuiLayer());
	}

	~Client() 
	{

	}


};

Alice::Application* Alice::CreateApplication() {
	return new Client();
}