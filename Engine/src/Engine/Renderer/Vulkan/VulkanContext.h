#pragma once

#include "../RenderContext.h"
#include <string>
#include <vector>
#include <array>
#include<vulkan/vulkan.h>
#include<glm/glm.hpp>
#include <optional>

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};

		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}


	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

const std::vector<Vertex> vertices = {
	{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};


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


class VulkanContext : public RenderContext {
public:
	VulkanContext();
	~VulkanContext();

	void BeginFrame() override;
	void EndFrame() override;

	//static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	//	auto app = reinterpret_cast<VulkanContext*>(glfwGetWindowUserPointer(window));
	//	app->m_FramebufferResized = true;
	//}

private:
	uint32_t currentFrame = 0;
	
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
	void cleanupSwapChain();
	void recreateSwapChain();
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
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	VkCommandPool m_CommandPool;
	std::vector<VkCommandBuffer> m_CommandBuffers;

	//Syncronization
	void createSyncObjects();
	std::vector<VkSemaphore> m_ImageAvailableSemaphores;
	std::vector<VkSemaphore> m_RenderFinishedSemaphores;
	std::vector<VkFence> m_InFlightFences;
	bool m_FramebufferResized = false;


};

