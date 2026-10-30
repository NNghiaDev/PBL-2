cmake_minimum_required(VERSION 3.15)
project(HospitalManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include paths
include_directories(
    include
    vendor/imgui
    vendor/imgui/backends
)

# ImGui sources
set(IMGUI_SOURCES
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

# Project sources
file(GLOB_RECURSE CORE_SOURCES "src/core/*.cpp")
file(GLOB_RECURSE DAO_SOURCES "src/dao/*.cpp")
file(GLOB_RECURSE GUI_SOURCES "src/gui/*.cpp")

add_executable(HMS 
    src/main.cpp 
    ${CORE_SOURCES} 
    ${DAO_SOURCES}
    ${GUI_SOURCES}
    ${IMGUI_SOURCES}
)

# Link GLFW and Windows OpenGL libraries
target_link_libraries(HMS PRIVATE
    glfw3
    opengl32
    gdi32
    imm32
)
