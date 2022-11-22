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
		ALICE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Alice::Event& event) override
	{
		ALICE_TRACE("{0}", event);
	}
};

class Sandbox : public Alice::Application {
public: 
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() 
	{

	}


};

Alice::Application* Alice::CreateApplication() {
	return new Sandbox();
}