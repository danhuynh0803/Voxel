#include "renderer/vulkan_context.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "core/log.hpp"

namespace cfv {

VulkanContext::VulkanContext(const std::string& appName) :
  mAppName(appName)
{
    CreateInstance();
    SetupDebugMessenger();
    SelectPhysicalDevice();
}

VulkanContext::~VulkanContext()
{
    if (mEnableLayers) {
        DestroyDebugUtilsMessengerEXT(mInstance, mDebugMessenger, nullptr);
    }

    vkDestroyInstance(mInstance, nullptr);
}

void VulkanContext::CreateInstance()
{
    #ifdef NDEBUG
        mEnableLayers = false;
    #else
        mEnableLayers = true;
    #endif

    VkApplicationInfo info{};
    info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName   = mAppName.c_str();
    info.applicationVersion = VK_MAKE_VERSION(1,0,0);
    info.pEngineName        = "voxel";
    info.engineVersion      = VK_MAKE_VERSION(1,0,0);
    info.apiVersion         = VK_API_VERSION_1_0;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    // For debug messenger callback
    if (mEnableLayers) {
        extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    if (!SupportsExtensions(extensions)) {
        throw std::runtime_error("Missing support for certain glfwExtensions");
    }

    VkInstanceCreateInfo createInfo{};
    createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &info;
    createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    // Validation layers
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation",
    };

    if (mEnableLayers && !SupportsLayers(validationLayers)) {
        throw std::runtime_error("Missing support for certain layers");
    }

    if (mEnableLayers) {
        createInfo.enabledLayerCount   = validationLayers.size();
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    VkResult result =
        vkCreateInstance(&createInfo,
                         nullptr,
                         &mInstance);

    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create vkInstance");
    }
}

void VulkanContext::SelectPhysicalDevice()
{
    uint32_t count = 0;
    vkEnumeratePhysicalDevices(mInstance, &count, nullptr);
    CORE_INFO("Found {0} devices", count);

    if (count = 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support");
    }

    std::vector<VkPhysicalDevice> devices(count);
    vkEnumeratePhysicalDevices(mInstance, &count, devices.data());
    CORE_INFO("Found {0} devices", count);
    CORE_INFO("Devices.size {0}", devices.size());
    for (const auto& device : devices)
    {
        CORE_INFO("Checking suitability");
        if (IsDeviceSuitable(device))
        {
            mPhysicalDevice = device;
            return;
        }
    }

    if (mPhysicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("Failed to find a suitable GPU");
    }
}

bool VulkanContext::IsDeviceSuitable(VkPhysicalDevice device)
{
    // Check device property and feature support
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    // TODO have some scoring system to select the best GPU
    // but for now just select the first to match all desired
    // properties and features
    return
         deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
      && deviceFeatures.multiDrawIndirect
      && deviceFeatures.geometryShader
      && deviceFeatures.sparseBinding
    ;
}

void VulkanContext::SwapBuffers()
{

}

bool VulkanContext::SupportsExtensions(
  const char** extList
, uint32_t extListSize
)
{
    std::vector<const char*> extensions;
    for (uint32_t i = 0; i < extListSize; ++i)
    {
        extensions.emplace_back(extList[i]);
    }

    return SupportsExtensions(extensions);
}

bool VulkanContext::SupportsExtensions(
  const std::vector<const char*>& extensions
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
            if (strcmp(extension, supported.extensionName) == 0) {
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

bool VulkanContext::SupportsLayers(
  const std::vector<const char*>& layers
)
{
    bool hasSupport = true;
    // Get available layers
    uint32_t count = 0;
    vkEnumerateInstanceLayerProperties(&count,
                                       nullptr);

    std::vector<VkLayerProperties> supportedLayers(count);
    vkEnumerateInstanceLayerProperties(&count,
                                       supportedLayers.data());

    // Check if desired layers are supported
    for (const auto& layer : layers) {
        bool isFound = false;
        for (const auto& supported : supportedLayers) {
            if (strcmp(layer, supported.layerName) == 0) {
                isFound = true;
                break;
            }
        }

        if (!isFound) {
            CORE_WARN("{} layer is not supported!", layer);
            hasSupport = false;
        }
    }

    return hasSupport;
}

void VulkanContext::SetupDebugMessenger()
{
    if (!mEnableLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT info{};
    info.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
                         | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                         | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
                       //| VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT // Enable to dump general dbg
    ;

    info.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
                         | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                         | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
    ;

    info.pfnUserCallback = DebugCallback;
    info.pUserData       = nullptr;

    if (CreateDebugUtilsMessengerEXT(mInstance, &info, nullptr, &mDebugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to setup Debug Messenger");
    }
}

VkResult VulkanContext::CreateDebugUtilsMessengerEXT(
  VkInstance instance
, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo
, const VkAllocationCallbacks* pAllocator
, VkDebugUtilsMessengerEXT* pDebugMessenger
)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void VulkanContext::DestroyDebugUtilsMessengerEXT(
  VkInstance instance
, VkDebugUtilsMessengerEXT debugMessenger
, const VkAllocationCallbacks* pAllocator
)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::DebugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity
, VkDebugUtilsMessageTypeFlagsEXT messageType
, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
, void* pUserData
)
{
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        CORE_ERROR("Validation layer: {}", pCallbackData->pMessage);
    }

    return VK_FALSE;
}

}
