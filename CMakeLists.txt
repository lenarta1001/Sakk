cmake_minimum_required(VERSION 3.10)
project(Sakk)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_DIR "C:/Users/Gabi/vcpkg/installed/x64-windows/share/sdl2")

find_package(SDL2 CONFIG REQUIRED)

add_executable(Sakk
    babu.cpp
    eltolas.cpp
    jatekallas.cpp
    lepes.cpp
    poz.cpp
    tabla.cpp
    szamolo.cpp
)

target_link_libraries(Sakk PRIVATE SDL2::SDL2 SDL2::SDL2main)