#include "core/application.hpp"
#include <iostream>

namespace cfv {

Application::Application(const ApplicationProps& props)
{

}

void Application::OnInit()
{

}

void Application::Run()
{
    std::cout << "Hello" << std::endl;
}

void Application::Shutdown()
{

}

};
