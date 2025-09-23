#pragma once


extern Application* CreateApplication();

int main() {
	auto app = CreateApplication();
	app->Run();
	delete app;
	return 0;
}