#pragma once
#include "../RenderContext.h"
#include <glad/glad.h>

class ENGINE_API OpenGLContext : public RenderContext {
public:
	OpenGLContext();
	~OpenGLContext();

    void Init() override;
    void Shutdown() override;
    void BeginFrame() override;
    void EndFrame() override;

private:
	void InitGlad();

    // OpenGL specific members
};
