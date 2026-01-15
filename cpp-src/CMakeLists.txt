cmake_minimum_required(VERSION 3.16)

project(coreutils-cpp LANGUAGES CXX)

# --- Options ---
option(BUILD_TESTING "Build the testing tree." ON)

# --- Standard C++ Settings ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Output Directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Include Paths ---
# Make the 'include' directory globally available to all targets in this project
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Subdirectories ---
add_subdirectory(src)
add_subdirectory(external)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
