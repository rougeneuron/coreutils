#include <iostream>
#include <vector>
#include <string_view>
#include <cstdlib>
#include <span>

void print_help() {
    std::cout << "Usage: true [ignored command line arguments]\n"
              << "  or:  true OPTION\n"
              << "Exit with a status code indicating success.\n\n"
              << "      --help     display this help and exit\n"
              << "      --version  output version information and exit\n";
}

void print_version() {
    std::cout << "true (coreutils-cpp) 0.1\n";
}

int main(int argc, char* argv[]) {
    std::vector<std::string_view> args(argv, argv + argc);

    if (args.size() > 1) {
        if (args[1] == "--help") {
            print_help();
            return EXIT_SUCCESS;
        }
        if (args[1] == "--version") {
            print_version();
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}
