#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include "core/application.hpp"
#include "core/window.hpp"
#include "core/log.hpp"

namespace cfv {

Application::Application(const ApplicationProps& props)
{
    // Init core modules
    Log::Init();

    WindowProps windowProps(props.title, props.width, props.height);
    mWindow = std::make_unique<Window>(windowProps);
}

Application::~Application()
{
}

void Application::OnInit()
{

}

void Application::Run()
{
    while (!glfwWindowShouldClose(mWindow->GetNativeWindow()))
    {
        mWindow->OnUpdate();
    }
}

void Application::Shutdown()
{
    isRunning = false;
}

};
