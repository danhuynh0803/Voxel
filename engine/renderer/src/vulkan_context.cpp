#include "renderer/vulkan_context.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "core/log.hpp"

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

    // TODO debug wrappers
    SupportsExtensions(glfwExtensions, glfwExtensionCount);

    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    VkResult result =
        vkCreateInstance(&createInfo,
                         nullptr,
                         &mInstance);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create vkInstance");
    }

    // Validation layers
}

VulkanContext::~VulkanContext()
{
    vkDestroyInstance(mInstance, nullptr);
}

void VulkanContext::SwapBuffers()
{

}

bool VulkanContext::SupportsExtensions(
  const char** extList
, uint32_t extListSize
)
{
    std::vector<std::string> extensions;
    for (uint32_t i = 0; i < extListSize; ++i)
    {
        extensions.emplace_back(std::string(extList[i]));
    }

    return SupportsExtensions(extensions);
}

bool VulkanContext::SupportsExtensions(
  const std::vector<std::string>& extensions
)
{
    bool hasSupport = true;
    // Get available extensions
    uint32_t count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr,
                                           &count,
                                           nullptr);

    std::vector<VkExtensionProperties> supportedExtensions(count);
    vkEnumerateInstanceExtensionProperties(nullptr,
                                           &count,
                                           supportedExtensions.data());

    // Check if desired extensions are supported
    for (const auto& extension : extensions) {
        bool isFound = false;
        for (const auto& supported : supportedExtensions) {
            if (strcmp(extension.c_str(), supported.extensionName) == 0) {
                isFound = true;
                break;
            }
        }

        if (!isFound) {
            CORE_WARN("{} extension is not supported!", extension);
            hasSupport = false;
        }
    }

    return hasSupport;
}

}
