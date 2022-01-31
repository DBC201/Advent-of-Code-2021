#ifndef DAY1_H
#define DAY1_H

#include <utils/file_utils.h>
#include <00.h>

using utils::file_utils::get_lines;
using solutions::day_0::Day0;

namespace solutions::day_1 {
	const std::string day_id = "01";

	class Day1 : public Day0 {
	public:
		Day1(std::string filepath): Day0(filepath) {
			lines = get_lines<int>(filepath, [](auto x) {return stoi(x); });
		}

		int part1() {
			int increase_count = 0;
			for (int i = 0; i < lines.size() - 1; i++) {
				if (lines[i] < lines[i + 1]) {
					increase_count++;
				}
			}
			return increase_count;
		}

		int part2() {
			int increase_count = 0;
			int prev_sum = 0;
			for (int i = 0; i < lines.size() - 3; i++) {
				int curr_sum = lines[i] + lines[i + 1] + lines[i + 2];
				if (curr_sum > prev_sum) {
					increase_count++;
				}
				prev_sum = curr_sum;
			}
			return increase_count;
		}

	private:
		std::vector<int> lines;
	};

} // solutions::day_1

#endif // DAY1_H