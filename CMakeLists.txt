cmake_minimum_required(VERSION 3.20)
project(BapeInternal LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar JNI (Java Native Interface)
find_package(JNI REQUIRED)

# Includes
include_directories(src imgui minhook/include ${JNI_INCLUDE_DIRS})

# ImGui Source
file(GLOB IMGUI_SOURCES 
    imgui/imgui.cpp 
    imgui/imgui_draw.cpp 
    imgui/imgui_tables.cpp 
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_win32.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

# MinHook Source
file(GLOB MINHOOK_SOURCES
    minhook/src/*.c
    minhook/src/hde/*.c
)

# Project Source
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

add_library(BapeInternal SHARED ${PROJECT_SOURCES} ${IMGUI_SOURCES} ${MINHOOK_SOURCES})

target_link_libraries(BapeInternal PRIVATE opengl32 dwmapi ${JNI_LIBRARIES})

target_compile_definitions(BapeInternal PRIVATE 
    WIN32_LEAN_AND_MEAN 
    NOMINMAX 
    _CRT_SECURE_NO_WARNINGS
)
