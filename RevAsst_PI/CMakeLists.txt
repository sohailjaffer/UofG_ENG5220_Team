cmake_minimum_required(VERSION 3.12)
project(RevAsst_Exec)

include_directories(include)


file(GLOB SOURCE_FILES src/*.cpp src/main.cpp)

add_executable(RevAsst_Exec ${SOURCE_FILES})

# Link libraries including libgpiod, Bluetooth, and pthread
target_link_libraries(RevAsst_Exec PRIVATE pigpio rt bluetooth pthread gpiod)

target_compile_options(RevAsst_Exec PRIVATE -I${CMAKE_CURRENT_SOURCE_DIR}/include)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
