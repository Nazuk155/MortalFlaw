cmake_minimum_required(VERSION 3.24)
project(FreshMortalFlaw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Check if we are using GCC or Clang
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic )
endif()



# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(fmt REQUIRED)

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project

include_directories(.)

add_executable(FreshMortalFlaw
        main.cpp
        Player.cpp
        Player.h
        recthelper.h
        global.h
        gamebase.cpp
        gamebase.h
        examplegame.cpp
        examplegame.h
        MortalFlawState.cpp
        introstate.cpp
        plasmastate.cpp
        Enemy.cpp
        Enemy.h
        AngleHelper.h
        AngleHelper.cpp
        Card.cpp
        Card.h
        Card_Dagger.cpp
        Card_Dagger.h
        Card_Sword.cpp
        Card_Sword.h
        Ui_Bar.cpp
        Ui_Bar.h
        Card_ForgeStrike.cpp
        Card_ForgeStrike.h


)
target_link_libraries(${PROJECT_NAME}

        SDL2::Main
        SDL2::TTF
        SDL2::Image
        SDL2::Mixer
        fmt::fmt
)