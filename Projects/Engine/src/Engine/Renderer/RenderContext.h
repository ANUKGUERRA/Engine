#pragma once
#include "../Core.h"
#include <string>

enum class RenderAPI {
	Vulkan = 0,
	OpenGL = 1
};

std::string RenderAPIToString(RenderAPI api);

ENGINE_API class RenderContext
{
public:
	virtual ~RenderContext() = default;
	virtual void Init() = 0;
	virtual void Shutdown() = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	static RenderContext* Create(RenderAPI api);
};