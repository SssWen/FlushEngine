
#include <Flush.h>

class Sandbox : public Flush::Application
{
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

Flush::Application* Flush::CreateApplication()
{
	return new Sandbox();
}