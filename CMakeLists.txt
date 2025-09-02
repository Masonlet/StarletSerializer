cmake_minimum_required(VERSION 3.20)
project(StarletParsers)

add_library(StarletParsers STATIC)

file(GLOB_RECURSE PARSER_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE PARSER_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/inc/StarletParsers/**/*hpp)

target_sources(StarletParsers PRIVATE ${PARSER_SRC} PUBLIC ${PARSE_HEADERS})

target_include_directories(StarletParsers PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>)
