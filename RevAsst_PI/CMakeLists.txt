cmake_minimum_required(VERSION 3.12)
project(RevAsst_Exec)

include_directories(include)

file(GLOB SOURCE_FILES src/*.cpp src/main.cpp)

add_executable(RevAsst_Exec ${SOURCE_FILES})

target_link_libraries(RevAsst_Exec pigpio rt)

# Add Bluetooth flags and libraries manually
find_library(BLUETOOTH_LIB bluetooth)
find_library(BLUETOOTH_LIB_NAME NAMES bluetooth)
if(BLUETOOTH_LIB AND BLUETOOTH_LIB_NAME)
    target_link_libraries(RevAsst_Exec PRIVATE ${BLUETOOTH_LIB})
else()
    message(WARNING "Bluetooth library not found. Modify as needed.")
endif()

target_compile_options(RevAsst_Exec PRIVATE -I${CMAKE_CURRENT_SOURCE_DIR}/include)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
