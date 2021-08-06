# Third-party vendor libraries

# glad
add_subdirectory(glad)
set_target_properties(glad PROPERTIES FOLDER "Vendor")

# glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)
set_target_properties(glfw PROPERTIES FOLDER "Vendor")

#target_compile_definitions(
#    glfw
#    PUBLIC
#        -DGLFW_INCLUDE_NONE
#        #-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
#)

add_definitions(
    -DGLFW_INCLUDE_NONE
    #-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)

# glm
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "glm/")
#add_subdirectory(glm)
#set_target_properties(glm PROPERTIES FOLDER "Vendor")

# imgui
add_subdirectory(imgui)
set_target_properties(imgui PROPERTIES FOLDER "Vendor")

# stb
#add_library(stb INTERFACE)
#target_include_directories(stb INTERFACE "stb/")
#set_target_properties(stb PROPERTIES FOLDER "Vendor")
