#include "VulkanContext.h"
#include <GLFW/glfw3.h>
#include "../../Logger.h"

#include <vector>



VulkanContext::VulkanContext() {
	CreateInstance();
	pickPhysicalDevice();
}

VulkanContext::~VulkanContext(){
	vkDestroyInstance(m_Instance, nullptr);
	LOG_SUCCESS("Vulkan Instance destroyed.");
}


void VulkanContext::BeginFrame() {

}
void VulkanContext::EndFrame() {

}

void VulkanContext::CreateInstance()
{
	VkApplicationInfo appInfo = {};

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Renderer";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
	{
		LOG_ERROR("Failed to create Vulkan Instance!");
		return;
	}

	LOG_SUCCESS("Vulkan Instance created successfully!");

	unsigned int extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	LOG_INFO("Available Extensions:");
	for (const auto& extension : extensions)
	{
		LOG_INFO("\t{0}", extension.extensionName);
	}

}

void VulkanContext::pickPhysicalDevice() {
	unsigned int deviceCount = 0;
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		LOG_ERROR("Failed to find GPUs with Vulkan support!");
		return;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

	LOG_INFO("Available Devices:");
	for (const auto& device : devices)
	{
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		LOG_INFO("Device Name: {0}", deviceProperties.deviceName);
	}
}
