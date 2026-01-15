# Implement `true` Utility in Modern C++

## Overview
The `true` utility is the simplest program in coreutils. It does nothing and exits with a success status code (`EXIT_SUCCESS`). However, it serves as an excellent starting point to establish our C++ infrastructure and demonstrate key modern C++ concepts compared to the original C implementation.

## Functionality
-   **Behavior**: Exit with status 0.
-   **Options**:
    -   `--help`: Display usage information and exit.
    -   `--version`: Display version information and exit.
-   **Arguments**: Any non-option arguments are ignored.

## Learning Objectives (C++ vs C)

### 1. Program Entry & Return
-   **Topic**: `main` function signature and return types.
-   **C++20**: Use `EXIT_SUCCESS` (from `<cstdlib>`) explicitly. Explore `std::exit` vs returning from main.

### 2. Argument Parsing
-   **Topic**: Handling `argc` and `argv`.
-   **C Usage**: Iterating `char** argv` with raw loops and `strcmp`.
-   **Modern C++**:
    -   Constructing `std::span<char*>` or `std::vector<std::string_view>` from `argv` to avoid raw pointer arithmetic.
    -   Using `std::string_view` for efficient, non-allocating string comparisons (`arg == "--help"`).

### 3. Output Streams
-   **Topic**: IO operations.
-   **C Usage**: `printf` for help text.
-   **Modern C++**:
    -   Use `std::cout` for standard output.
    -   Discuss `std::ios::sync_with_stdio(false)` for performance parity with C stdio, even if not critical for `true`.
    -   Demonstrate `std::format` (if available in compiler) or `fmt` library for formatted strings.

### 4. Build System
-   **Topic**: Adding a new target.
-   **Task**: Define `add_executable(true_cpp src/true.cpp)` in CMake and ensure it links correctly.

## Implementation Tasks
- [ ] Create `cpp-src/src/true.cpp`.
- [ ] Implement `main` with `std::vector<std::string_view>` arg parsing.
- [ ] Handle `--help` and `--version`.
- [ ] Add CMake target.
- [ ] Verify against original `true` using the test suite.
