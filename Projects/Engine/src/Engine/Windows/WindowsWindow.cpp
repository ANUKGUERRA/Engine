#include "WindowsWindow.h"

namespace Engine {
	WindowsWindow::WindowsWindow(const WindowData& data) {
		Init(data);
		Logger::Log("Window created with GLFW", LogLevel::SUCCESS);
	}
	
	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowData& data) {
		m_Data.Title = data.Title;
		m_Data.Height = data.Height;
		m_Data.Width = data.Width;

		if (!glfwInit()) {
			Logger::Log("Could not initialize GLFW!", LogLevel::ERROR);
		}

		//TODO: WinowHint: Puede cambiar dependiendo de la necesidad de vulakn, hacer pantalla Resizable ...
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		if (!m_Window) {
			Shutdown();
			Logger::Log("Failed tocreate GLFW window", LogLevel::ERROR);
		}

		glfwMakeContextCurrent(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::Shutdown() {
		if (m_Window) {
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}
		glfwTerminate();
	}

	Window* Window::Create(const WindowData& data) {
		return new WindowsWindow(data);
	}
}