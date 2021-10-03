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

private:
    bool SupportsExtensions(const std::vector<std::string>&);

private:
    VkInstance mInstance;
};

};
