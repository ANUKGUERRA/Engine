#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include "../../Logger.h"

OpenGLContext::OpenGLContext() {
    InitGlad();
	Init();
}

OpenGLContext::~OpenGLContext() {
}

void OpenGLContext::InitGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        LOG_ERROR("Failed to initialize GLAD");
    else
        LOG_INFO("GLAD initialized successfully!");
}

void OpenGLContext::Init() {
    LOG_INFO("OpenGLContext initialized.");
    glClearColor(1.f, 1.f, 0.f, 1.0f); // Set background color
}

void OpenGLContext::Shutdown() {
}

void OpenGLContext::BeginFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLContext::EndFrame() {

}
