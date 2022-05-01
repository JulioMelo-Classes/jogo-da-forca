cmake_minimum_required(VERSION 3.5)
project(Jogo_Da_Forca VERSION 0.1 LANGUAGES CXX )

set ( CMAKE_CXX_FLAGS "-Wall" )

include_directories( include )

set( APP_NAME "program" )
add_executable( ${APP_NAME}
                src/main.cpp
                src/forca.cpp
                src/forca_text.cpp )

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 14)