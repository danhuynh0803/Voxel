#pragma once
#include <string>
#include <memory>

namespace cfv {

struct ApplicationProps
{
    std::string title;
    uint32_t width;
    uint32_t height;
};

class Application
{
public:
    Application(const ApplicationProps& props = {"cfv", 1600, 900});
    ~Application() {}

    static Application& Get() { return *instance; }

    virtual void OnInit();
    virtual void Run();
    virtual void Shutdown();

private:
    static std::unique_ptr<Application> instance;
};

};
