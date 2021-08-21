#include "core/application.hpp"

extern cfv::Application* CreateApplication();

int main()
{
    cfv::ApplicationProps props {
        "Voxel Engine",
        1600,
        900
    };

    cfv::Application app(props);
    app.Run();

    return 0;
}
