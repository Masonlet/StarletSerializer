cmake_minimum_required(VERSION 3.20)
project(StarletParsers)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SUPPRESS_REGENERATION ON)

add_library(StarletParsers STATIC)

file(GLOB_RECURSE PARSER_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE PARSER_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/inc/StarletParsers/*.hpp)

source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source Files" FILES ${PARSER_SRC})
source_group(TREE ${CMAKE_SOURCE_DIR}/inc PREFIX "Header Files" FILES ${PARSER_HEADERS})

target_sources(StarletParsers PRIVATE ${PARSER_SRC} PUBLIC ${PARSER_HEADERS})
target_include_directories(StarletParsers PUBLIC "${CMAKE_SOURCE_DIR}/inc")

include(FetchContent)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(StarletMath GIT_REPOSITORY https://github.com/masonlet/starletmath.git GIT_TAG main)
FetchContent_MakeAvailable(StarletMath)

target_link_libraries(StarletParsers PUBLIC StarletMath)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "External")
