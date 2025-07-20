cmake_minimum_required(VERSION 3.10)
project(Sakk)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/Users/Gabi/vcpkg/installed/x64-mingw-dynamic")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)

add_executable(Sakk
    babu.cpp
    eltolas.cpp
    jatekallas.cpp
    lepes.cpp
    poz.cpp
    tabla.cpp
    szamolo.cpp
    ablak.cpp
    fenstring.cpp
    main.cpp
)

target_link_libraries(
    Sakk
    PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2::SDL2_gfx
)