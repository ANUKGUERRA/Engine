    #pragma once
#include <memory>
#include "Windows/Window.h"
#include "Renderer/RenderContext.h"

class Application {
public:
    Application(RenderAPI api = RenderAPI::Vulkan);
    virtual ~Application();

    void Run();
    static std::unique_ptr<Window> m_Window;

private:
	void SetRenderAPI(RenderAPI api);

    std::unique_ptr<RenderContext> m_RenderContext;

    RenderAPI m_CurrentAPI;
    bool m_Running = true;
};

Application* CreateApplication();