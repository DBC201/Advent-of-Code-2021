#include <12.h>

using solutions::day_12::Day12;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "no filename given" << std::endl;
        exit(EXIT_FAILURE);
    }

    Day12 day12(argv[1]);

    std::cout << day12.part1() << std::endl;
    std::cout << day12.part2() << std::endl;

    return EXIT_SUCCESS;
}