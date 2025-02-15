#include "../Logger.h"
#include "RenderContext.h"
#include "Vulkan/VulkanContext.h"
#include "OpenGL/OpenGLContext.h"

RenderContext* RenderContext::Create(RenderAPI api) {
    switch (api) {
    case RenderAPI::Vulkan:
        return new VulkanContext();

    case RenderAPI::OpenGL:
        return new OpenGLContext();

    default:
        LOG_ERROR("No rendering API selected");
        return nullptr;
    }
}

std::string RenderAPIToString(RenderAPI api) {
    switch (api) {
    case RenderAPI::Vulkan:
        return "Vulkan";
    case RenderAPI::OpenGL:
        return "OpenGL";
    default:
        return "InvlidValue";
    }
}
