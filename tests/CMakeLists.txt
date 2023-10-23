

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_executable(test_g test.cpp)

target_link_libraries(
  test_g
  GTest::gtest_main
)

#add_test(test_g test_g)
include(GoogleTest)
gtest_discover_tests(test_g DISCOVERY_MODE PRE_TEST)
