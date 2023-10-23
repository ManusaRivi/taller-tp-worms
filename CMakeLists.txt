cmake_minimum_required(VERSION 3.16)

project(worms)

set(CMAKE_CXX_STANDARD 17)

include_directories(libs/box2d/include/box2d)

add_subdirectory(libs/box2d)

#file(GLOB_RECURSE SERVER ./server/*.cpp)

#add_library(server_lib STATIC ${SERVER})

add_executable(server "server/server_box2d_poc.cpp")

#target_link_libraries(server server_lib box2d)

target_link_libraries(server box2d)

# Va a haber otro ejecutable para el editor.

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)


# Se Buildena los tests
project(TEST_RUNNER)

add_subdirectory(tests)
include(GoogleTest)
enable_testing()
#gtest_discover_tests(test_g DISCOVERY_MODE PRE_TEST)
#add_test(NAME TESTING COMMAND $<TARGET_FILE:test_g>)
