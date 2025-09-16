#pragma once
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

vk::Instance create_instance(const char* applicationName, vk::DebugUtilsMessengerEXT &debugMessenger) {

	uint32_t version{ 0 };
	vkEnumerateInstanceVersion(&version);

	std::cout << "System can support vulkan Variant: " << VK_API_VERSION_VARIANT(version)
		<< ", Major: " << VK_API_VERSION_MAJOR(version)
		<< ", Minor: " << VK_API_VERSION_MINOR(version)
		<< ", Patch: " << VK_API_VERSION_PATCH(version) << '\n';


	version &= ~(0xFFFU);
	version = VK_MAKE_API_VERSION(0, 1, 0, 0);

	vk::ApplicationInfo appInfo = vk::ApplicationInfo(
		applicationName,
		version,
		"UNVE",
		version,
		version
	);

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	std::cout << "extensions to be requested:\n";

	for (const char* extensionName : extensions) {
		std::cout << "\t\"" << extensionName << "\"\n";
	}

	vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
		vk::InstanceCreateFlags(),
		&appInfo,
		0, nullptr,
		static_cast<uint32_t>(extensions.size()), extensions.data()
	);

	return vk::createInstance(createInfo);
}