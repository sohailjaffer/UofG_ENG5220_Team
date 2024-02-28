cmake_minimum_required(VERSION 3.12)
project(RevAsst_Exec)

# Include headers
include_directories(include)

# Add your source files
file(GLOB SOURCE_FILES src/*.cpp src/main.cpp)

# Generate the executable
add_executable(RevAsst_Exec ${SOURCE_FILES})

# Link libraries
target_link_libraries(RevAsst_Exec pigpio rt)

# Set C++ compiler flags
target_compile_options(RevAsst_Exec PRIVATE -I${CMAKE_CURRENT_SOURCE_DIR}/include)

# Specify the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)  # Default to Release if not specified
endif()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
