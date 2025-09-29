#include "WindowsWindow.h"

WindowsWindow::WindowsWindow(const WindowSpecs& data) {
	Init(data);
}

WindowsWindow::~WindowsWindow() {
	Shutdown();
}



void WindowsWindow::Init(const WindowSpecs& data) {
	m_Data.Title = data.Title;
	m_Data.Height = data.Height;
	m_Data.Width = data.Width;

	if (!glfwInit()) {
	}

	//TODO: WinowHint: Puede cambiar dependiendo de la necesidad de vulakn, hacer pantalla Resizable ...
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);


	m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_Window, this);
	//glfwSetFramebufferSizeCallback(m_Window, VulkanContext::framebufferResizeCallback);


	glfwMakeContextCurrent(m_Window);
}

void WindowsWindow::OnUpdate() {
	glfwPollEvents();
}

void WindowsWindow::Shutdown() {
	if (m_Window) {
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}
	glfwTerminate();
}