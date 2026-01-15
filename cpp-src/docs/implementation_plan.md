# Porting GNU Coreutils to Modern C++: An Overview

## Goal
Port the GNU `coreutils` repository from C to Modern C++ (C++17/20) as a learning exercise. The goal is to leverage modern C++ features (RAII, standard library containers, smart pointers, `std::filesystem`) while maintaining functionality and passing the existing test suite.

## User Review Required
> [!IMPORTANT]
> This is a massive undertaking. The strategy below focuses on an iterative approach, starting with the build system and simple utilities.

## Proposed Steps

### Phase 1: Infrastructure & Build System
1.  **Directory Structure**: Create `cpp-src` as the project root with standard layout:
    -   `cpp-src/src/`: Implementation files (`.cpp`).
    -   `cpp-src/include/`: Public/Internal headers (`.hpp`).
    -   `cpp-src/tests/`: Unit and integration tests.
    -   `cpp-src/docs/`: Design docs and manuals.
    -   `cpp-src/external/`: Third-party dependencies (e.g., `googletest`, `fmt`).
    -   `cpp-src/cmake/`: Custom CMake modules.
2.  **Initialize CMake**: Create `cpp-src/CMakeLists.txt` and `cpp-src/cmake/`.
    -   Root CMake project for the port.
    -   Configure standard paths (`CMAKE_RUNTIME_OUTPUT_DIRECTORY`, etc.).
    -   Isolate from parent repo; treat it as an external dependency source only if needed.

### Phase 2: Iterative Porting
Select a simple utility (e.g., `true`, `yes`, `echo`) to start.

#### Step 2.1: Bootstrap New File
1.  Create `cpp-src/src/<tool>.cpp`.
2.  **Handle Dependencies**:
    -   Use `cpp-src/include` for common helpers.
    -   If using `gnulib` features, create a clean C++ wrapper in `cpp-src/src/common/` or `cpp-src/external/`.

#### Step 2.2: Refactor to C++
Iteratively apply modern C++ patterns:
1.  **Strings**: Replace `char*` string manipulation with `std::string` and `std::string_view`.
2.  **Containers**: Replace raw arrays with `std::vector`, `std::array`.
3.  **IO**: Replace `printf`/`scanf` with `std::iostream` (carefully, for performance) or `std::format` (C++20).
4.  **Resources**: Use smart pointers (`std::unique_ptr`) and RAII for file handles.
5.  **Filesystem**: Use `std::filesystem` for file operations (replacing `stat`, `opendir`, etc.).
6.  **Command Line Parsing**: Consider using a C++ CLI library (like `CLI11` or `Boost.ProgramOptions`) or wrap `getopt` in a C++ friendly interface. *Note: Coreutils has strict POSIX compliance requirements, so wrapper around `getopt_long` is safer.*

### Phase 3: Verification
1.  **Integration Tests**: Run the existing Perl/Shell test suite against the new binaries.
    -   Ensure `make check` (or equivalent) passes.
2.  **Unit Tests**: Introduce a C++ unit testing framework (e.g., Google Test/Catch2) for new internal logic.

## Roadmap Example
1.  **Setup**: Create directory structure (`src`, `include`, `tests`, etc.) and `CMakeLists.txt`.
2.  **Target**: `src/true.c` -> `cpp-src/src/true.cpp`.
    -   Create `cpp-src/src/true.cpp`.
    -   Add executable target in `cpp-src/src/CMakeLists.txt` (or main list).
    -   Verify functionality.
    -   Copy source.
    -   Compile as C++ in the new location.
    -   Verify functionality.
3.  **Target**: `src/yes.c` -> `cpp-src/yes.cpp`.
    -   Port logic to use `std::string_view` and `std::cout`.
    -   Maintain behavior parity.
4.  **Target**: `src/cat.c` (File IO).
    -   Use `std::fstream` or memory mapped files.
    -   Refactor buffer management.

## Verification Plan

### Automated Tests
-   **Legacy Tests**: Run the existing test suite in `tests/` against the build artifacts.
    ```bash
    # Example for running a specific test
    ./tests/get-test-metrics.pl src/true
    ```
-   **New Build**:
    ```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
    ctest # If CMake tests are configured
    ```

### Manual Verification
-   Compare output of original and ported tools.
    ```bash
    ./src/true && echo "Original Success"
    ./cpp-src/build/src/true && echo "Port Success"
    ```
