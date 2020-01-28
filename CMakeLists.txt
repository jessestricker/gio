cmake_minimum_required(VERSION 3.10)
project(GIO VERSION 0.1.0 LANGUAGES CXX)

# global
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(TestBigEndian)
TEST_BIG_ENDIAN(gio_big_endian)
if (gio_big_endian)
    set(GIO_NATIVE_ENDIAN BigEndian)
else ()
    set(GIO_NATIVE_ENDIAN LittleEndian)
endif ()

configure_file(include/gio/config.hpp.in include/gio/config.hpp @ONLY)

# library
add_library(gio
        src/config.cpp)

target_include_directories(gio
        PRIVATE include/gio
        INTERFACE include)
target_include_directories(gio
        PRIVATE ${PROJECT_BINARY_DIR}/include/gio
        INTERFACE ${PROJECT_BINARY_DIR}/include)

# test
add_executable(gio-test
        test/catch/main.cpp
        test/config.cpp
        test/span.cpp)
target_link_libraries(gio-test gio)
