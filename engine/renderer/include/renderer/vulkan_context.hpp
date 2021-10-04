#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>

namespace cfv {

class VulkanContext
{
public:
    VulkanContext(const std::string&);
    ~VulkanContext();
    void SwapBuffers();

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
      VkDebugUtilsMessageSeverityFlagBitsEXT msgSeverity
    , VkDebugUtilsMessageTypeFlagsEXT msgType
    , const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
    , void* pUserData
    );

private:
    void CreateInstance();
    void SelectPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device);

    bool SupportsExtensions(const char** extList, uint32_t extListSize);
    bool SupportsExtensions(const std::vector<const char*>& extensions);
    bool SupportsLayers(const std::vector<const char*>& layers);
    void SetupDebugMessenger();

    // Extension proxy functions
    VkResult CreateDebugUtilsMessengerEXT(
      VkInstance instance
    , const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo
    , const VkAllocationCallbacks* pAllocator
    , VkDebugUtilsMessengerEXT* pDebugMessenger
    );

    void DestroyDebugUtilsMessengerEXT(
      VkInstance instance
    , VkDebugUtilsMessengerEXT debugMessenger
    , const VkAllocationCallbacks* pAllocator
    );

private:
    VkInstance mInstance;
    VkDebugUtilsMessengerEXT mDebugMessenger;
    VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
    bool mEnableLayers = false;
    std::string mAppName;
};

};
