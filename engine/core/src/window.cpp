#include "core/window.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace cfv {

Window::Window(const WindowProps& props)
  : mTitle(props.title),
    mWidth(props.width),
    mHeight(props.height)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void Window::OnUpdate()
{
    glfwPollEvents();
    //context->SwapBuffers();
}

}
