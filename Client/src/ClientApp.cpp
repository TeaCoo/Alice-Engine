#include <Alice.h>

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

//#define CLIENT_GUI
#define MESH_DEBUG
//#define GUI_DEBUG
class Client : public Alice::Application {
public: 
	Client() 
	{
#ifdef CLIENT_GUI
		PushOverlay(new Alice::ImGui_Engine_Editer());
#elif defined MESH_DEBUG
		PushOverlay(new Alice::Mash_Debug());
#elif defined GUI_DEBUG
		//PushLayer(new ExampleLayer());
#endif 
	}

	~Client() 
	{

	}
};

Alice::Application* Alice::CreateApplication() {
	return new Client();
}