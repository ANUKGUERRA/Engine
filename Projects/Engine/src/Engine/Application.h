    #pragma once
#include <memory>
#include "Core.h"
#include "Windows/Window.h"
#include "Renderer/RenderContext.h"

class ENGINE_API Application {
public:
    Application(RenderAPI api = RenderAPI::Vulkan);
    virtual ~Application();

    void Run();

private:
	void SetRenderAPI(RenderAPI api);//TODO: Add the option for the user to switch between APIs by pressing a key or in UI(This Method is not used anywhere yet)

    std::unique_ptr<Window> m_Window;
    std::unique_ptr<RenderContext> m_RenderContext;

    RenderAPI m_CurrentAPI;
    bool m_Running = true;
};

Application* CreateApplication();