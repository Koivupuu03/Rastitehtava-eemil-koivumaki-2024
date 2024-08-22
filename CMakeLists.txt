cmake_minimum_required(VERSION 3.5)

project(rastitehtava2024 LANGUAGES C)

add_executable(rastitehtava2024 main.c)

install(TARGETS rastitehtava2024
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
