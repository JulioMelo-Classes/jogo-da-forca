cmake_minimum_required(VERSION 3.5)
project(all_any_none_program VERSION 0.1 LANGUAGES CXX )

set ( CMAKE_CXX_FLAGS "-Wall" )

include_directories( include )

set( APP_NAME "program" )
add_executable( ${APP_NAME}
                src/main.cpp )

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 14)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/palavrasP.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scores.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)