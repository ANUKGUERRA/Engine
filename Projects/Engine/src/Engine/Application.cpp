#include "Application.h"
#include <GLFW/glfw3.h>
#include "Renderer/Vulkan/VulkanContext.h"

std::unique_ptr<Window> Application::m_Window = nullptr;

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


void Application::Run() {
    for (int jid = GLFW_JOYSTICK_1; jid <= GLFW_JOYSTICK_LAST; jid++) {
        if (glfwJoystickPresent(jid)) {
            const char* name = glfwGetJoystickName(jid);
            if (name)
                LOG_INFO("Controller {} connected: {}", jid, name);
            else
                LOG_INFO("Controller {} connected", jid);
        }
    }

    while (m_Running) {
        m_Window->OnUpdate();

        m_RenderContext->BeginFrame();
        m_RenderContext->EndFrame();

        if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
            GLFWgamepadstate state;
            if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
                const float deadzone = 0.15f;

                float lx = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
                float ly = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
                float rx = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
                float ry = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];

                if (std::abs(lx) > deadzone || std::abs(ly) > deadzone) {
                    LOG_INFO("Left Stick -> X: {}, Y: {}", lx, ly);
                }
                if (std::abs(rx) > deadzone || std::abs(ry) > deadzone) {
                    LOG_INFO("Right Stick -> X: {}, Y: {}", rx, ry);
                }
            }
        }

        if (glfwGetKey(static_cast<GLFWwindow*>(m_Window->GetWindow()), GLFW_KEY_ESCAPE))
            m_Running = false;
    }
}


//void Application::Run() {
//    while (m_Running) {
//        m_Window->OnUpdate();
//
//        static bool spacePressedLastFrame = false;
//
//        int spaceState = glfwGetKey(static_cast<GLFWwindow*>(m_Window->GetWindow()), GLFW_KEY_SPACE);
//
//        if (spaceState == GLFW_PRESS && !spacePressedLastFrame) {
//            LOG_INFO("Space key pressed");
//            RenderAPI newAPI = (m_CurrentAPI == RenderAPI::Vulkan) ? RenderAPI::OpenGL : RenderAPI::Vulkan;
//            SetRenderAPI(newAPI);
//            spacePressedLastFrame = true;  // Mark as pressed
//        }
//        else if (spaceState == GLFW_RELEASE) {
//            spacePressedLastFrame = false;  // Reset when key is released
//        }
//
//        m_RenderContext->BeginFrame();
//        m_RenderContext->EndFrame();
//    }
//}

 