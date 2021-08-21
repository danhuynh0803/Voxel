target_include_directories(
    Engine
    PUBLIC
        "include"
)

set(RENDERER_HEADERS
    include/renderer/vulkan_context.hpp
)

set(RENDERER_SRC
    src/vulkan_context.cpp
)

target_sources(
    Engine
    PRIVATE
        ${RENDERER_SRC}
)
