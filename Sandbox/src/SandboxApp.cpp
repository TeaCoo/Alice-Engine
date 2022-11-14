#include <Alice.h>

class Sandbox : public Alice::Application {
public: 
	Sandbox() 
	{

	}

	~Sandbox() 
	{

	}


};

Alice::Application* Alice::CreateApplication() {
	return new Sandbox();
}