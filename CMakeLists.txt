cmake_policy(SET CMP0048 NEW)

project(Voxel
    #VERSION 0.0
    #DESCRIPTION "Voxel Engine"
    #LANGUAGES CXX
)


cmake_minimum_required(VERSION 3.16)

# Set all libs to be static
option(BUILD_SHARED_LIBS OFF)

# Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if (EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "build must be out of source")
endif()

add_subdirectory(engine)
add_subdirectory(third_party)
