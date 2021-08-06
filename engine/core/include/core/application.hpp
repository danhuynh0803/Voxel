#pragma once

namespace cfv {

class Application
{
public:
    Application(const ApplicationProps& props = {"cfv", 1600, 900});
    ~Application();

    static Application& Get() { return *instance; }

    virtual void OnInit();
    virtual void Run();
    virtual void Shutdown();

private:
};

};
