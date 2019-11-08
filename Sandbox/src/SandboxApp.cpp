#include <Cyberspace.h>

class Sandbox : public Cyberspace::Application
{
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Cyberspace::Application* Cyberspace::CreateApplication()
{
	return new Sandbox();
}