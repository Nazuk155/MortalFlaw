cmake_minimum_required(VERSION 3.24)
project(FreshMortalFlaw)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)



# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)



# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project

include_directories(.)

add_executable(FreshMortalFlaw
        main.cpp
        Player.cpp
        Player.h
        recthelper.h
        global.h


)
target_link_libraries(${PROJECT_NAME}
        SDL2::Main

        SDL2::Image
        SDL2::Mixer
)