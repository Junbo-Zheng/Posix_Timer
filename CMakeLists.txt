cmake_minimum_required(VERSION 3.23)

project(timer LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Werror -Wno-format -g)

add_library(posix_timer STATIC timer.c)

add_executable(timer main.c)
target_link_libraries(timer posix_timer rt)
target_include_directories(timer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
