target_include_directories(
    Engine
    PUBLIC
        "include"
)

set(CORE_HEADERS
    include/core/application.hpp
    include/core/window.hpp
)

set(CORE_SRC
    src/application.cpp
    src/window.cpp
)

target_sources(
    Engine
    PRIVATE
        ${CORE_SRC}
        ${CORE_HEADERS}
)
