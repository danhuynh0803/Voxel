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

class Window;

class Application
{
public:
    Application(const ApplicationProps& props = {"cfv", 1600, 900});
    ~Application();

    static Application& Get() { return *mInstance; }

    virtual void OnInit();
    virtual void Run();
    virtual void Shutdown();

    Window& GetWindow() const { return *mWindow; }

private:
    static std::unique_ptr<Application> mInstance;
    std::unique_ptr<Window> mWindow;
    bool isRunning = true;
};

};
