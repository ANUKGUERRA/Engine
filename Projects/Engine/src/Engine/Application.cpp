#include "Application.h"
#include <GLFW/glfw3.h>
#include "Renderer/Vulkan/VulkanContext.h"

Application::Application(RenderAPI api) : m_CurrentAPI(api)
{
    m_Window.reset(Window::Create());
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

    m_RenderContext.reset(RenderContext::Create(api));

    m_CurrentAPI = api;
}


void Application::Run() {
    while (m_Running) {
        m_Window->OnUpdate();
    }
}
