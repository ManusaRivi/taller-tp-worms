

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SERVER ../server/*.cpp)
file(GLOB_RECURSE CLIENT ../client/*.cpp)
file(GLOB_RECURSE EDITOR ../editor/*.cpp)
file(GLOB_RECURSE COMMON ../common/*.cpp)





add_executable(test_g test.cpp test_socket.cpp)

target_compile_definitions(test_g PRIVATE TESTING)

target_link_libraries(
  test_g
  GTest::gtest_main
  server_lib box2d yaml-cpp common_lib Threads::Threads
  client_lib ${SDL2PP_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES}
)

#add_test(test_g test_g)
include(GoogleTest)
gtest_discover_tests(test_g DISCOVERY_MODE PRE_TEST)
