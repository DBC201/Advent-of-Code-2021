#include <14.h>

using solutions::day_14::Day14;

int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "no filename given" << std::endl;
        exit(EXIT_FAILURE);
    }

    Day14 day14(argv[1]);

    std::cout << day14.part1() << std::endl;
    std::cout << day14.part2() << std::endl;

    return EXIT_SUCCESS;
}
