#pragma once

#include "../RenderContext.h"
#include <string>
#include <vector>
#include<vulkan/vulkan.h>
#include <optional>

const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };


struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


class ENGINE_API VulkanContext : public RenderContext {
public:
	VulkanContext();
	~VulkanContext();

	void BeginFrame() override;
	void EndFrame() override;

private:
	//Instance
	void createInstance();
	VkInstance m_Instance;

	//PhysicalDevice
	void pickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;


	//Queue families
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;


	//LogicalDevice
	void createLogicalDevice();
	VkDevice m_Device = VK_NULL_HANDLE;


	//Window Surface
	void createSurface();
	VkSurfaceKHR m_Surface;

	//Swap chain
	void createSwapChain();
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	std::vector<const char*> getRequiredExtensions();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createImageViews();
	VkSwapchainKHR m_SwapChain;
	std::vector<VkImage> m_SwapChainImages;
	std::vector<VkImageView> m_SwapChainImageViews;
	VkFormat m_SwapChainImageFormat;
	VkExtent2D m_SwapChainExtent;

	//RenderPass
	void createRenderPass();
	VkRenderPass m_RenderPass;

	//Pipeline
	void createGraphicsPipeline();
	VkPipeline m_GraphicsPipeline;
	VkPipelineLayout m_PipelineLayout;

	//Shaders
	std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	//FrameBuffer
	void createFramebuffers();
	std::vector<VkFramebuffer> m_SwapChainFramebuffers;

	//Comand
	void createCommandPool();
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	VkCommandPool m_CommandPool;
	VkCommandBuffer m_CommandBuffer;

	//Syncronization
	void createSyncObjects();
	VkSemaphore m_ImageAvailableSemaphore;
	VkSemaphore m_RenderFinishedSemaphore;
	VkFence m_InFlightFence;

	float CurrentTime;
	float LastTime;


};

