cmake_minimum_required(VERSION 3.8)

project(worms)

set(CMAKE_CXX_STANDARD 17)

# Box2d
include_directories(libs/box2d/include/box2d)
add_subdirectory(libs/box2d)

# Para SDL2pp
add_subdirectory(libs/SDL2pp)
include_directories(${SDL2PP_INCLUDE_DIRS})

#file(GLOB_RECURSE SERVER ./server/*.cpp)

#add_library(server_lib STATIC ${SERVER})
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -std=c++17")

file(GLOB_RECURSE SERVER ./server/*.cpp)
file(GLOB_RECURSE CLIENT ./client/*.cpp)
file(GLOB_RECURSE EDITOR ./editor/*.cpp)

#target_link_libraries(server server_lib box2d)
add_library(server_lib STATIC ${SERVER})
add_library(client_lib STATIC ${CLIENT})
add_library(editor_lib STATIC ${EDITOR})

add_executable(server "server/main.cpp")
add_executable(client "client/main.cpp")
add_executable(editor "editor/main.cpp")

target_link_libraries(client ${SDL2PP_LIBRARIES})

# Va a haber otro ejecutable para el editor.
target_link_libraries(server server_lib box2d)
# Agregar: SDL y Qt
target_link_libraries(client client_lib)
target_link_libraries(editor editor_lib)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)


# Se Buildena los tests
project(TEST_RUNNER)

add_subdirectory(tests)
include(GoogleTest)
enable_testing()
#gtest_discover_tests(test_g DISCOVERY_MODE PRE_TEST)
#add_test(NAME TESTING COMMAND $<TARGET_FILE:test_g>)
