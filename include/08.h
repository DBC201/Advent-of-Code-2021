#ifndef DAY8_H
#define DAY8_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/set_utils.h>
#include <unordered_set>
#include <cmath>

using utils::file_utils::get_lines;
using utils::string_utils::split_by_string;
using utils::set_utils::set_difference;
using utils::set_utils::set_equal;
using utils::set_utils::set_intersection;
using utils::set_utils::set_unification;

using solutions::day_0::Day0;

namespace solutions::day_8 {
	const std::string day_id = "08";

	class Day8: public Day0 {
	public:
		Day8(std::string filepath) : Day0(filepath) {
			displays = get_lines<display_type_t>(
                filepath,
				[](auto line) {
					auto tokens = split_by_string(line, " | ");
					return display_type_t(split_by_string(tokens[0], " "), split_by_string(tokens[1], " "));
				}
			);
		}

		int part1() {
			int desired_count = 0;

			for (const auto& nums : displays) {
				for (const auto& num_string : nums.second) {
					auto length = num_string.length();
					if (length == 2 || length == 4 || length == 3 || length == 7) {
						desired_count++;
					}
				}
			}

			return desired_count;
		}

        int part2() {
            int sum = 0;
            for (const auto& nums : displays) {
                sum += decode_entries(nums.first, nums.second);
            }

            return sum;
        }

	private:
		using display_type_t = std::pair<std::vector<std::string>, std::vector<std::string>>;
		using display_container_t = std::vector<display_type_t>;
        display_container_t displays;

        int decode_entries(std::vector<std::string> input, std::vector<std::string> output) {
            using num_t = std::unordered_set<char>;
            using num_vector_t = std::vector<num_t>;

            num_vector_t nums(10);

            auto string_to_num = [](std::string str) {
                num_t num;
                for (const auto& c : str) {
                    num.insert(c);
                }
                return num;
            };

            std::string one;
            std::string four;
            std::string seven;
            std::string eight;
            for (const auto& num_string : input) {
                auto length = num_string.length();
                if (length == 2) {
                    one = num_string;
                }
                else if (length == 4) {
                    four = num_string;
                }
                else if (length == 3) {
                    seven = num_string;
                }
                else if (length == 7) {
                    eight = num_string;
                }
            }

            nums[1] = string_to_num(one);
            nums[4] = string_to_num(four);
            nums[7] = string_to_num(seven);
            nums[8] = string_to_num(eight);

            auto top = set_difference(nums[7], set_intersection<num_t>({ nums[1], nums[7] }));
            auto top_left_and_middle = set_difference(nums[4], nums[1]);
            auto bottom_left_and_bottom = set_difference(nums[8], set_unification<num_t>({ nums[4], top }));

            num_t middle;
            num_t top_right;
            num_t bottom_left;

            for (const auto& str : input) {
                if (str.length() == 6) {
                    num_t curr = string_to_num(str);
                    num_t res = set_intersection<num_t>({ curr, nums[1] });
                    if (res.size() == 1) {
                        nums[6] = curr;
                        top_right = set_difference(nums[8], curr);
                    }
                    else if (res.size() == 2) {
                        if (set_intersection<num_t>({ curr, top_left_and_middle }).size() == 2) {
                            nums[9] = curr;
                            bottom_left = set_difference(nums[8], curr);
                        }
                        else {
                            nums[0] = curr;
                            middle = set_difference(nums[8], curr);
                        }
                    }
                    else {
                        std::cerr << "invalid representation " << str << std::endl;
                        return EXIT_FAILURE;
                    }
                }
                if (!middle.empty() && !top_right.empty() && !bottom_left.empty()) {
                    break;
                }
            }

            num_t bottom = set_difference(bottom_left_and_bottom, bottom_left);
            num_t bottom_right = set_difference(nums[1], top_right);
            num_t top_left = set_difference(top_left_and_middle, middle);

            nums[2] = set_unification<num_t>({ top, top_right, middle, bottom_left, bottom });
            nums[3] = set_unification<num_t>({ top, top_right, middle, bottom_right, bottom });
            nums[5] = set_unification<num_t>({ top, top_left, middle, bottom_right, bottom });

            int sum = 0;
            for (int digit = 0; digit < output.size(); digit++) {
                auto num = string_to_num(output[digit]);
                for (int i = 0; i < 10; i++) {
                    if (set_equal<num_t>(num, nums[i])) {
                        sum += i * pow(10, output.size() - digit - 1);
                        break;
                    }
                }
            }
            return sum;
        }
	};
} // solutions::day_8

#endif // DAY8_H