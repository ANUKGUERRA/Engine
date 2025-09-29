#pragma once

#include <string>
#include <set>
#include <vector>
#include <queue>
#include <functional>
#include <fstream>
#include <array>
#include <optional>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <cstdlib>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Windows/Window.h"


const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

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

struct Vertex {
	glm::vec3 pos;
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
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};


const std::vector<Vertex> vertices = {

	//Front face (z = -0.5, looking down -Z axis)
	{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // bottom-left
	{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}},  // top-left  
	{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},  // top-right
	{{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},  // bottom-right

	//Back face (z = 0.5, looking down +Z axis)
	{{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},  // bottom-right
	{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},  // top-right
	{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}},  // top-left
	{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},  // bottom-left

	//Up face (y = 0.5, looking down -Y axis)
	{{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // front-left
	{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}},  // back-left
	{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},  // back-right
	{{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},  // front-right

	//Down face (y = -0.5, looking down +Y axis)
	{{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},  // front-right
	{{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}},  // back-right
	{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}},  // back-left
	{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},  // front-left

	//Right face (x = 0.5, looking down -X axis)
	{{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},  // front-bottom
	{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},  // front-top
	{{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},  // back-top
	{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}},  // back-bottom

	//Left face (x = -0.5, looking down +X axis)
	{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}},  // back-bottom
	{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}},  // back-top
	{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},  // front-top
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}   // front-bottom
};

const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4,
	8, 9, 10, 10, 11, 8,
	12, 13, 14, 14, 15, 12,
	16, 17, 18, 18, 19, 16,
	20, 21, 22, 22, 23, 20
};

struct AppSpecs {

    std::string Name = "Engine";
	std::string WorkingDirectory;
};




class Application
{
public:
	Application(const AppSpecs& applicationSpecification = AppSpecs());
	~Application();

	static Application& Get();

	void Run();

	float GetTime();
	GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

private:
	void Init();
	void Shutdown();

private:
	AppSpecs m_Specification;
	GLFWwindow* m_WindowHandle = nullptr;
	bool m_Running = false;

	float m_TimeStep = 0.0f;
	float m_FrameTime = 0.0f;
	float m_LastFrameTime = 0.0f;

	bool framebufferResized = false;

	std::unique_ptr<Window> m_Window;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	uint32_t currentFrame = 0;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;



	void initWindow();

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	void initVulkan();

	void mainLoop();

	void cleanupSwapChain();

	void cleanup();

	void recreateSwapChain();

	void createInstance();

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void setupDebugMessenger();

	void createSurface();

	void pickPhysicalDevice();

	void createLogicalDevice();

	void createSwapChain();

	void createImageViews();

	void createRenderPass();

	void createGraphicsPipeline();

	void createFramebuffers();

	void createCommandPool();

	void createCommandBuffers();

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void createSyncObjects();

	void drawFrame();

	void createVertexBuffer();

	void createIndexBuffer();

	void createUniformBuffers();

	void updateUniformBuffer(uint32_t currentImage);

	void createDescriptorSetLayout();

	void createDescriptorPool();

	void createDescriptorSets();


	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, 
		VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	std::vector<const char*> getRequiredExtensions();

	bool checkValidationLayerSupport();

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	static std::vector<char> readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {

			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
};

Application* CreateApplication();