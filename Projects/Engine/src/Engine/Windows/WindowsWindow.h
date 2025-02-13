#pragma once
#include "Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowData& data);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		int GetWidth() const override { return m_Data.Width; }
		int GetHeight() const override { return m_Data.Height; }
		void* GetWindow() const override { return m_Window; }
	private:
		void Init(const WindowData& props);
		void Shutdown();

		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}