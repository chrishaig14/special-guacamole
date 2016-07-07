cmake_minimum_required(VERSION 3.5)

project(City)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11" )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB src
        "*.cpp"
        "SDL/*.cpp")

set(SOURCE_FILES ${src} SDL/Music.cpp SDL/Music.h SDL/Sound.cpp SDL/Sound.h SDL/Renderer.cpp SDL/Renderer.h SDL/Text.cpp SDL/Text.h SDL/Price.cpp SDL/Price.h SDL/Draggable.cpp SDL/Draggable.h SDL/GameGrid.cpp SDL/GameGrid.h SDL/Cell.cpp SDL/Cell.h SDL/City.cpp SDL/City.h)

add_executable(city main.cpp ${SOURCE_FILES})

target_link_libraries(city SDL2 SDL2_image SDL2_ttf SDL2_mixer)
