cmake_minimum_required(VERSION 3.18)
project(GA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main # release-1.10.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(SRC STATIC src/Alarm.cpp src/Message.cpp src/Application.cpp src/Tag.cpp)

enable_testing()



add_executable(${PROJECT_NAME} src/main.cpp )
add_executable(${PROJECT_NAME}-ut src/test.cpp )

target_link_libraries(${PROJECT_NAME} SRC )
target_link_libraries(${PROJECT_NAME}-ut gtest_main)



include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)