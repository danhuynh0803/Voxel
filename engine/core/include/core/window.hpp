#pragma once

#include <string>
#include <memory>
#include "renderer/vulkan_context.hpp"

struct GLFWwindow;

namespace cfv {

struct WindowProps
{
    std::string title;
    uint32_t width, height;

    WindowProps(const std::string& t,
                uint32_t w,
                uint32_t h)
        : title(t), width(w), height(h) {}
};

class Window
{
public:
    Window(const WindowProps& props);
    ~Window();

    void OnUpdate();
    GLFWwindow* GetNativeWindow() const { return mWindow; }
    uint32_t GetWidth() const { return mWidth; }
    uint32_t GetHeight() const { return mHeight; }

private:
    GLFWwindow* mWindow;

    std::string mTitle;
    uint32_t mWidth, mHeight;
    std::unique_ptr<VulkanContext> mContext;
};

}
