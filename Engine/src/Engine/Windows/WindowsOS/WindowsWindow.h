#pragma once
#include "../Window.h"
#include <GLFW/glfw3.h>

class WindowsWindow : public Window {
public:
	WindowsWindow(const WindowSpecs& data);
	virtual ~WindowsWindow();

	void OnUpdate() override;
	int GetWidth() const override { return m_Data.Width; }
	int GetHeight() const override { return m_Data.Height; }
	void* GetWindow() const override { return m_Window; }
private:
	void Init(const WindowSpecs& props);
	void Shutdown();

	GLFWwindow* m_Window;
	WindowSpecs m_Data;
};