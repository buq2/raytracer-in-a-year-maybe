cmake_minimum_required(VERSION 3.5)
project(raytracer VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

#enable_testing()

add_subdirectory(src)

option(BUILD_TESTS "Test with code coverage" TRUE)
IF (BUILD_TESTS)
    add_subdirectory(test)
ENDIF()
