#ifndef DAY6_H
#define DAY6_H

#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <numeric>
#include <00.h>

using solutions::day_0::Day0;
using utils::file_utils::get_lines;
using utils::string_utils::split_by_string;
using utils::string_utils::convert_string_vector;

namespace solutions::day_6 {
	const std::string day_id = "06";

	class Day6 : public Day0 {
	public:
		Day6(std::string filepath) : Day0(filepath) {
			squids = get_lines<std::vector<int>>(
				filepath,
				[](std::string line) {
					return convert_string_vector<int>(split_by_string(line, ","));
				}
			)[0];
		};

		auto part1() {
			return simulate_days(80);
		}

		auto part2() {
			return simulate_days(256);
		}
	private:
		uint_fast64_t simulate_days(uint_fast64_t day_count) {
			std::vector<uint_fast64_t> days(9, 0);
			for (const auto& s : squids) {
				days[s]++;
			}

			for (auto i = 0; i < day_count; i++) {
				uint_fast64_t zero = days[0];
				for (auto j = 1; j < days.size(); j++) {
					days[j - 1] = days[j];
				}
				days[days.size() - 1] = 0;
				days[6] += zero;
				days[8] += zero;
			}
			return std::accumulate(days.begin(), days.end(), (uint_fast64_t)0);
		}
		std::vector<int> squids;
	};

} // solutions::day_5

#endif // DAY6_H