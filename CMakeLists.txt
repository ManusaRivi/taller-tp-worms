cmake_minimum_required(VERSION 3.8)

project(worms)

set(CMAKE_CXX_STANDARD 17)

# Para Threads
find_package(Threads REQUIRED)

# Box2d
include_directories(libs/box2d/include/box2d)
add_subdirectory(libs/box2d)

# Para SDL2pp
SET(SDL2PP_WITH_IMAGE ON) # Para soporte de imagenes
SET(SDL2PP_WITH_MIXER ON) # Para soporte de sonido
SET(SDL2PP_WITH_TTF ON) # Para soporte de texto
add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
add_subdirectory(libs/SDL2pp)
include_directories(${SDL2PP_INCLUDE_DIRS})

# Para yaml-cpp
include_directories(libs/yaml-cpp/include/yaml-cpp)
add_subdirectory(libs/yaml-cpp)

# Para Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})

#file(GLOB_RECURSE SERVER ./server/*.cpp)


#add_library(server_lib STATIC ${SERVER})
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline -std=c++17 -D _POSIX_C_SOURCE=200809L")

# Configura las banderas de compilación con -fPIC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

file(GLOB_RECURSE SERVER ./server/*.cpp)
file(GLOB_RECURSE CLIENT ./client/*.cpp)
file(GLOB_RECURSE EDITOR ./editor/*.cpp)
file(GLOB_RECURSE COMMON ./common/*.cpp)

#target_link_libraries(server server_lib box2d)
add_library(server_lib STATIC ${SERVER})
add_library(client_lib STATIC ${CLIENT})
add_library(editor_lib STATIC ${EDITOR})
add_library(common_lib STATIC ${COMMON})

add_executable(server "server/main.cpp")
add_executable(client "client/main.cpp")
add_executable(editor "editor/main.cpp")

# Va a haber otro ejecutable para el editor.
target_link_libraries(server server_lib box2d yaml-cpp common_lib Threads::Threads ${SDL2PP_LIBRARIES})
target_link_libraries(client client_lib ${SDL2PP_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} yaml-cpp common_lib Threads::Threads)
target_link_libraries(editor editor_lib ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} yaml-cpp)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)


# Se Buildean los tests
project(TEST_RUNNER)

add_subdirectory(tests)
include(GoogleTest)
enable_testing()
#gtest_discover_tests(test_g DISCOVERY_MODE PRE_TEST)
#add_test(NAME TESTING COMMAND $<TARGET_FILE:test_g>)
