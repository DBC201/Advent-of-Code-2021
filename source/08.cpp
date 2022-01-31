#include <08.h>

using solutions::day_8::Day8;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "no filename given" << std::endl;
        exit(EXIT_FAILURE);
    }

    Day8 day8(argv[1]);

    std::cout << day8.part1() << std::endl;
    std::cout << day8.part2() << std::endl;

    return EXIT_SUCCESS;
}
