#pragma once
#include "Core.h"
#include "Windows/Window.h"
#include <memory>

namespace Engine {
    class ENGINE_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();
}