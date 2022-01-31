#include <01.h>
#include <02.h>
#include <03.h>
#include <04.h>
#include <05.h>
#include <06.h>
#include <07.h>
#include <08.h>
#include <09.h>
#include <12.h>
#include <14.h>

using solutions::day_1::Day1;
using solutions::day_2::Day2;
using solutions::day_3::Day3;
using solutions::day_4::Day4;
using solutions::day_5::Day5;
using solutions::day_6::Day6;
using solutions::day_7::Day7;
using solutions::day_8::Day8;
using solutions::day_9::Day9;
using solutions::day_12::Day12;
using solutions::day_14::Day14;

bool assert(auto actual, auto expected) {
	if (actual != expected) {
		std::cerr << "Failed: (actual)" << actual << " == (expected)" << expected << std::endl;
		return false;
	}
	else {
		std::cerr << "Passed: (actual)" << actual << " == (expected)" << expected << std::endl;
		return true;
	}
}

bool test_day(auto day_id, auto day, auto p1_solution, auto p2_solution) {
	bool passed = true;
	std::cout << "--------------------" << std::endl;
	std::cout << "Testing " << day_id << std::endl;
	std::cout << "Part 1: ";
	try {
		passed = !assert(day.part1(), p1_solution) ? false : passed;
	}
	catch (std::exception& e) {
		std::cerr << "Failed with error: " << e.what() << std::endl;
		passed = false;
	}
	std::cout << "Part 2: ";
	try {
		passed = !assert(day.part2(), p2_solution) ? false : passed;
	}
	catch (std::exception& e) {
		std::cerr << "Failed with error: " << e.what() << std::endl;
		passed = false;
	}
	return passed;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "project root absolute path not given" << std::endl;
		return EXIT_FAILURE;
	}

	std::vector<std::string> failed_tests;

	const std::string root = argv[1];

	auto get_input_path = [&](std::string day) {
		return root + "/inputs" + "/" + day + ".txt";
	};

	auto day1_id = solutions::day_1::day_id;
	Day1 day1(get_input_path(day1_id));
	if (!test_day(day1_id, day1, 1292, 1262)) {
		failed_tests.push_back(day1_id);
	}

	auto day2_id = solutions::day_2::day_id;
	Day2 day2(get_input_path(day2_id));
	if (!test_day(day2_id, day2, 1855814, 1845455714)) {
		failed_tests.push_back(day2_id);
	}

	auto day3_id = solutions::day_3::day_id;
	Day3 day3(get_input_path(day3_id));
	if (!test_day(solutions::day_3::day_id, day3, 2595824, 2135254)) {
		failed_tests.push_back(day3_id);
	}

	auto day4_id = solutions::day_4::day_id;
	Day4 day4(get_input_path(day4_id));
	if (!test_day(day4_id, day4, 34506, 7686)) {
		failed_tests.push_back(day4_id);
	}

	auto day5_id = solutions::day_5::day_id;
	Day5 day5(get_input_path(day5_id));
	if (!test_day(solutions::day_5::day_id, day5, 7318, 19939)) {
		failed_tests.push_back(day5_id);
	}

	auto day6_id = solutions::day_6::day_id;
	Day6 day6(get_input_path(day6_id));
	if (!test_day(day6_id, day6, 366057, 1653559299811)) {
		failed_tests.push_back(day6_id);
	}

	auto day7_id = solutions::day_7::day_id;
	Day7 day7(get_input_path(day7_id));
	if (!test_day(day7_id, day7, 352331, 99266250)) {
		failed_tests.push_back(day7_id);
	}

	auto day8_id = solutions::day_8::day_id;
	Day8 day8(get_input_path(day8_id));
	if (!test_day(day8_id, day8, 367, 974512)) {
		failed_tests.push_back(day8_id);
	}

	auto day9_id = solutions::day_9::day_id;
	Day9 day9(get_input_path(day9_id));
	if (!test_day(day9_id, day9, 512, 1600104)) {
		failed_tests.push_back(day9_id);
	}

	auto day12_id = solutions::day_12::day_id;
	Day12 day12(get_input_path(day12_id));
	if (!test_day(day12_id, day12, 3779, 96988)) {
		failed_tests.push_back(day12_id);
	}

	auto day14_id = solutions::day_14::day_id;
	Day14 day14(get_input_path(day14_id));
	if (!test_day(day14_id, day14, 2937, 3390034818249)) {
		failed_tests.push_back(day14_id);
	}

	if (failed_tests.empty()) {
		std::cout << "--------------------" << std::endl;
		std::cout << "all tests passed" << std::endl;;
		return EXIT_SUCCESS;
	}
	else {
		std::cerr << "--------------------" << std::endl;
		std::cerr << "failed tests:" << std::endl;
		for (const auto& id : failed_tests) {
			std::cerr << id << ", ";
		}
		std::cerr << std::endl;
		return EXIT_FAILURE;
	}
}
