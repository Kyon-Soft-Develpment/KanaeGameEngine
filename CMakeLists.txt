cmake_minimum_required(VERSION 3.20)

project(KanaeGameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable C++98 compatibility warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-poison-system-directories)
endif()

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(KANAE_BUILD_EXAMPLES "Build example projects" ON)

# Dependencies
include(FetchContent)

# JSON for Modern C++
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(json)

# GLFW for window management
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLM for math operations
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.9
)
FetchContent_MakeAvailable(imgui)

# Native File Dialog
FetchContent_Declare(
    nativefiledialog
    GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
    GIT_TAG master
)
FetchContent_MakeAvailable(nativefiledialog)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Create ImGui implementation library
add_library(imgui_impl STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
)
target_include_directories(imgui_impl PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_impl PUBLIC
    glfw
    Vulkan::Vulkan
)

# Create Native File Dialog library
add_library(nfd STATIC
    ${nativefiledialog_SOURCE_DIR}/src/nfd_common.c
    ${nativefiledialog_SOURCE_DIR}/src/nfd_cocoa.m
)
target_include_directories(nfd PUBLIC
    ${nativefiledialog_SOURCE_DIR}/src/include
)
target_link_libraries(nfd PRIVATE
    "-framework AppKit"
)

# Create engine library
add_library(KanaeEngine STATIC
    CoreEngine/Graphics/VulkanContext.cpp
    CoreEngine/Graphics/GraphicsDevice.cpp
    CoreEngine/Launcher/Launcher.cpp
)
target_include_directories(KanaeEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${glm_SOURCE_DIR}
)
target_link_libraries(KanaeEngine PUBLIC
    glfw
    Vulkan::Vulkan
    imgui_impl
    nlohmann_json::nlohmann_json
    nfd
    glm
)

# Create launcher executable
add_executable(KanaeLauncher
    CoreEngine/Launcher/main.cpp
)
target_link_libraries(KanaeLauncher PRIVATE
    KanaeEngine
)

# Build examples
if(KANAE_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif() 