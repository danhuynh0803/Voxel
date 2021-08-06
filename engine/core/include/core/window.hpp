#pragma once

#include <string>

namespace cfv {

struct WindowProps
{
    std::string title;
    uint32_t width, height;

    WindowsProps(const std::string& t = "cfv",
                 uint32_t w = 1600,
                 uint32_t h = 900)
        : title(t), width(w), height(h) {}
};

struct GLFWwindow;

class Window
{
public:
    Window(const WindowProps& props);
    ~Window() = default;

    void OnUpdate();
    void* GetNativeWindow() const { return mWindow; }
    uint32_t GetWidth() const { return mWidth; }
    uint32_t GetHeight() const { return mHeight; }

private:
    GLFWwindow* mWindow;

    std::string mTitle;
    uint32_t mWidth, mHeight;
};

}
