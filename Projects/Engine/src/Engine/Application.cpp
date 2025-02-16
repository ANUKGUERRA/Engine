#include "Application.h"
#include <GLFW/glfw3.h>
#include "Renderer/Vulkan/VulkanContext.h"

Application::Application(RenderAPI api) : m_CurrentAPI(api)
{
    WindowData newWindowData;
    newWindowData.API = api;
    m_Window.reset(Window::Create(newWindowData));

	m_RenderContext.reset(RenderContext::Create(api));

    LOG_INFO("Application initialized with {} renderer", RenderAPIToString(api));
}

Application::~Application() {
    LOG_INFO("Application shutdown");
}

void Application::SetRenderAPI(RenderAPI api) {
    if (api == m_CurrentAPI) {
        return;
    }

    LOG_INFO("Switched from {} renderer to  {} renderer", RenderAPIToString(m_CurrentAPI), RenderAPIToString(api));

	m_Window.reset();
    WindowData newWindowData;
    newWindowData.API = api;
    m_Window.reset(Window::Create(newWindowData));

    m_RenderContext.reset(RenderContext::Create(api));

    m_CurrentAPI = api;
}


//void Application::Run() {
//    while (m_Running) {
//        m_Window->OnUpdate();
//    }
//}

void Application::Run() {
    while (m_Running) {
        m_Window->OnUpdate();

        static bool spacePressedLastFrame = false;

        int spaceState = glfwGetKey(static_cast<GLFWwindow*>(m_Window->GetWindow()), GLFW_KEY_SPACE);

        if (spaceState == GLFW_PRESS && !spacePressedLastFrame) {
            LOG_INFO("Space key pressed");
            RenderAPI newAPI = (m_CurrentAPI == RenderAPI::Vulkan) ? RenderAPI::OpenGL : RenderAPI::Vulkan;
            SetRenderAPI(newAPI);
            spacePressedLastFrame = true;  // Mark as pressed
        }
        else if (spaceState == GLFW_RELEASE) {
            spacePressedLastFrame = false;  // Reset when key is released
        }

        m_RenderContext->BeginFrame();
        m_RenderContext->EndFrame();
    }
}

 