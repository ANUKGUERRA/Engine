#pragma once


#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main() {
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif