#include <09.h>

using solutions::day_9::Day9;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "no filename given" << std::endl;
        exit(EXIT_FAILURE);
    }

    Day9 day9(argv[1]);

    std::cout << day9.part1() << std::endl;
    std::cout << day9.part2() << std::endl;

	return EXIT_SUCCESS;
}