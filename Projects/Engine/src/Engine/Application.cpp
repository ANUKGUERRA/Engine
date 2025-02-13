#include "Application.h"
#include <GLFW/glfw3.h>

namespace Engine {
    Application::Application() {
        m_Window.reset(Window::Create());
        Logger::Log("Application initialized", LogLevel::INFO);
    }

    Application::~Application() {
        Logger::Log("Application shutdown", LogLevel::INFO);
    }

    void Application::Run() {
        while (m_Running) {
            m_Window->OnUpdate();
        }
    }
}