cmake_minimum_required(VERSION 3.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

project(gametoo)

find_package(PkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED sdl2_image)
pkg_check_modules(SDL2_NET REQUIRED sdl2_net)

file(GLOB_RECURSE headers ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE resources ${CMAKE_SOURCE_DIR}/res/*)

set(destination "${CMAKE_CURRENT_BINARY_DIR}/res")

add_executable(gametoo ${sources} ${headers})
target_include_directories(gametoo PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS})
target_link_libraries(gametoo ${SDL2} ${SDL2_IMAGE} ${SDL2_NET})

add_custom_command(
    TARGET gametoo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:gametoo>/res
)
