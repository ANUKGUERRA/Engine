#pragma once

#include "../RenderContext.h"
#include<vulkan/vulkan.h>


class ENGINE_API VulkanContext : public RenderContext {
public:
	VulkanContext();
	~VulkanContext();

	void Init() override;
	void Shutdown() override;
	void BeginFrame() override;
	void EndFrame() override;


private:

	void CreateInstance();

	VkInstance m_Instance;

};

