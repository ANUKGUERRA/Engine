#pragma once

#include "../RenderContext.h"
#include<vulkan/vulkan.h>


class ENGINE_API VulkanContext : public RenderContext {
public:
	VulkanContext();
	~VulkanContext();

	void BeginFrame() override;
	void EndFrame() override;


private:

	void CreateInstance();
	void pickPhysicalDevice();

	VkInstance m_Instance;
	VkPhysicalDevice m_PhysicalDevice;

};

