#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "core/window.hpp"
#include "renderer/vulkan_context.hpp"

namespace cfv {

Window::Window(const WindowProps& props)
  : mTitle(props.title)
  , mWidth(props.width)
  , mHeight(props.height)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    mWindow = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);

    mContext = std::make_unique<VulkanContext>(props.title);
}

Window::~Window()
{
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Window::OnUpdate()
{
    glfwPollEvents();
    //mContext->SwapBuffers();
}

}
