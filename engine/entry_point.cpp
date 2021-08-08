#include "core/application.hpp"

extern cfv::Application* CreateApplication();

int main()
{
    cfv::Application app;
    app.Run();

    return 0;
}
