set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#add_library(Engine)

# for including EntryPoint.h
#target_include_directories(Engine PUBLIC "./")
add_executable(
    Engine
)

target_sources(
    Engine
    PUBLIC
        entry_point.cpp
)

if(NOT MSVC)
    find_package(X11 REQUIRED)
    link_libraries(${X11_LIBRARIES})
    add_definitions(-DVK_USE_PLATFORM_XLIB_KHR)
endif()

target_link_libraries(
    Engine
    PUBLIC
        glm
        imgui
        glad
        glfw
        spdlog
    PRIVATE
        Vulkan::Vulkan
        #stb
)

add_subdirectory(core)
add_subdirectory(renderer)
