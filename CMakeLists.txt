cmake_minimum_required(VERSION 3.18)
set( CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe" )
set( CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe" )
project(GenerateAlarms)
add_executable(${PROJECT_NAME} src/main.cpp src/logic.cpp)

add_custom_target(run
    COMMAND ${PROJECT_NAME}.exe
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running ${PROJECT_NAME}..."
)
