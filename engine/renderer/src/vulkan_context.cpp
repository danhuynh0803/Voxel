#include "renderer/vulkan_context.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace cfv {

VulkanContext::VulkanContext(const std::string& appName)
{
    // Creating VkInstance
    VkApplicationInfo info{};
    info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName   = appName.c_str();
    info.applicationVersion = VK_MAKE_VERSION(1,0,0);
    info.pEngineName        = "voxel";
    info.engineVersion      = VK_MAKE_VERSION(1,0,0);
    info.apiVersion         = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &info;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &mInstance);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create vkInstance");
    }
}

VulkanContext::~VulkanContext()
{

}

void VulkanContext::SwapBuffers()
{

}

}
