#pragma once
#include "../RenderContext.h"

class ENGINE_API OpenGLContext : public RenderContext {
public:
    void Init() override;
    void Shutdown() override;
    void BeginFrame() override;
    void EndFrame() override;

private:
    // OpenGL specific members
};
