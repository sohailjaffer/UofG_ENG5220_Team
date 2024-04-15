cmake_minimum_required(VERSION 3.12)
project(RevAsst_Exec)

include_directories(include)


set(GTEST_DIR /usr/src/gtest)


include_directories(${GTEST_DIR}/include)

# Set the source files
file(GLOB SOURCE_FILES src/*.cpp src/main.cpp)

# Add executable
add_executable(RevAsst_Exec ${SOURCE_FILES})

# Link libraries including libgpiod, Bluetooth, and pthread
target_link_libraries(RevAsst_Exec PRIVATE pigpio rt bluetooth pthread gpiod)

# Add Google Test library
target_link_libraries(RevAsst_Exec PRIVATE ${GTEST_DIR}/libgtest.a ${GTEST_DIR}/libgtest_main.a)

# Set compile options
target_compile_options(RevAsst_Exec PRIVATE -I${CMAKE_CURRENT_SOURCE_DIR}/include)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)