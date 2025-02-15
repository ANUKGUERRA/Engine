#pragma once


#ifdef ENGINE_PLATFORM_WINDOWS

extern Application* CreateApplication();

int main() {
	auto app = CreateApplication();
	//app->Run();
	app->SetRenderAPI(RenderAPI::OpenGL);
	delete app;
	return 0;
}

#endif