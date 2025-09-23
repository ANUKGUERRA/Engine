//#include "WindowsWindow.h"
//#include "../Renderer/Vulkan/VulkanContext.h"
//
//WindowsWindow::WindowsWindow(const WindowData& data) {
//	Init(data);
//	LOG_SUCCESS("Window created with GLFW");
//}
//
//WindowsWindow::~WindowsWindow() {
//	Shutdown();
//}
//
//
//
//void WindowsWindow::Init(const WindowData& data) {
//	m_Data.Title = data.Title;
//	m_Data.Height = data.Height;
//	m_Data.Width = data.Width;
//
//	if (!glfwInit()) {
//		LOG_ERROR("Could not initialize GLFW!");
//	}
//
//	//TODO: WinowHint: Puede cambiar dependiendo de la necesidad de vulakn, hacer pantalla Resizable ...
//	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//	if (data.API == RenderAPI::OpenGL)
//		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
//	else if (data.API == RenderAPI::Vulkan)
//		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//
//	m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
//	glfwSetWindowUserPointer(m_Window, this);
//	//glfwSetFramebufferSizeCallback(m_Window, VulkanContext::framebufferResizeCallback);
//
//	if (!m_Window) {
//		Shutdown();
//		LOG_ERROR("Failed tocreate GLFW window");
//	}
//
//	glfwMakeContextCurrent(m_Window);
//}
//
//void WindowsWindow::OnUpdate() {
//	glfwPollEvents();
//}
//
//void WindowsWindow::Shutdown() {
//	if (m_Window) {
//		glfwDestroyWindow(m_Window);
//		m_Window = nullptr;
//	}
//	glfwTerminate();
//}
//
//Window* Window::Create(const WindowData& data) {
//	return new WindowsWindow(data);
//}	