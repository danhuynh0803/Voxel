#include "core/application.hpp"

extern Application* CreateApplication();

int main()
{
    Application* app;
    app->Run();

    return 0;
}
