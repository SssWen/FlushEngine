#pragma once

#ifdef FLUSH_PLATFORM_WINDOW
extern Flush::Application* Flush::CreateApplication();
//Application* CreateApplication();
int main(int argc, char** argv)
{
	printf("Flush Eng");
	auto app = Flush::CreateApplication();
	app->Run();
	delete app;
}

#endif