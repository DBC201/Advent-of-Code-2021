#ifndef DAY7_H
#define DAY7_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <algorithm>

using utils::file_utils::get_lines;
using utils::string_utils::split_by_string;
using utils::string_utils::convert_string_vector;
using solutions::day_0::Day0;

namespace solutions::day_7 {
	const std::string day_id = "07";

	class Day7 : public Day0 {
	public:
		Day7(std::string filepath) : Day0(filepath) {
			crabs = get_lines<std::vector<int>>(
				filepath,
				[](auto line) {
					return convert_string_vector<int>(split_by_string(line, ","));
				}
			)[0];

			std::sort(crabs.begin(), crabs.end(), [](auto a, auto b) {return a < b; });
		}

		auto part1() {
			std::vector<int> dp(crabs[crabs.size() - 1] + 1, INT32_MAX);

			auto calculate_movement_cost = [&](int position) {
				int sum = 0;
				for (const auto& crab : crabs) {
					sum += std::abs(crab - position);
				}
				return sum;
			};

			for (int i = 0; i < dp.size(); i++) {
				dp[i] = calculate_movement_cost(i);
			}

			std::sort(dp.begin(), dp.end(), [](auto a, auto b) {return a < b; });

			return dp[0];
		}
		
		auto part2() {
			std::vector<uint_fast64_t> dp2(crabs[crabs.size() - 1] + 1, UINT_FAST64_MAX);

			auto calculate_movement_cost2 = [&](uint_fast64_t position) {
				uint_fast64_t sum = 0;
				for (const auto& crab : crabs) {
					uint_fast64_t margin = std::abs((int_fast64_t)crab - (int_fast64_t)position);
					uint_fast64_t fuel = (margin * (margin + 1)) / 2;
					sum += fuel;
				}
				return sum;
			};

			for (int i = 0; i < dp2.size(); i++) {
				dp2[i] = calculate_movement_cost2(i);
			}

			std::sort(dp2.begin(), dp2.end(), [](auto a, auto b) {return a < b; });
			return dp2[0];
		}

	private:
		std::vector<int> crabs;
	};
}

#endif // DAY7_H