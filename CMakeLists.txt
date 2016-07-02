cmake_minimum_required(VERSION 3.5)

project(City)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11" )

file(GLOB src
        "*.cpp"
        "SDL/*.cpp")

set(SOURCE_FILES ${src})

add_executable(city main.cpp ${SOURCE_FILES})

target_link_libraries(city SDL2 SDL2_image SDL2_ttf SDL2_mixer)
