#ifndef DAY3_H
#define DAY3_H

#include <00.h>
#include <utils/file_utils.h>
#include <thread>

using utils::file_utils::get_lines;
using solutions::day_0::Day0;

namespace solutions::day_3 {
	const std::string day_id = "03";

	int binary_string_to_int(std::string binary) {
		int res = 0;
		for (int i = 0; i < binary.length(); i++) {
			res += (binary[i] - '0') * pow(2, binary.length() - i - 1);
		}
		return res;
	}

	class Day3: public Day0 {
	public:
		Day3(std::string filepath): Day0(filepath) {
			lines = get_lines<std::string>(filepath, [](std::string line) {return line; });
			bit_count = count_bits(lines);
		}

		auto part1() {
			std::string gamma = "";
			std::string epsilon = "";
			for (const auto& bit : bit_count) {
				if (bit.first > bit.second) {
					gamma += '0';
					epsilon += '1';
				}
				else if (bit.second > bit.first) {
					gamma += '1';
					epsilon += '0';
				}
				else {
					std::cerr << "Equal amounts of bits idk" << std::endl;
					exit(EXIT_FAILURE);
				}
			}

			return binary_string_to_int(gamma) * binary_string_to_int(epsilon);
		}

		auto part2() {
			auto oxygen_rating = lines; // more
			auto oxygen_bit_count = bit_count;
			auto coo_rating = lines; // fewer
			auto coo_bit_count = bit_count;

			auto remove_binaries = [&](auto& binaries, auto& bit_count, auto l) {
				for (auto i = 0; i < bit_count.size(); i++) {
					auto bit_to_remove = l(bit_count[i].first, bit_count[i].second);
					if (binaries.size() == 1) {
						return;
					}
					for (auto it = binaries.begin(); it != binaries.end(); ) {
						if ((*it)[i] != bit_to_remove) {
							it = binaries.erase(it);
						}
						else {
							it++;
						}
					}
					bit_count = count_bits(binaries);
				}
			};

			auto oxygen_thread = std::thread([&]() {
				while (oxygen_rating.size() > 1) {
					remove_binaries(oxygen_rating, oxygen_bit_count, [](auto zero_count, auto one_count) {
						if (zero_count > one_count) {
							return '0';
						}
						else if (zero_count < one_count) {
							return '1';
						}
						else {
							return '1';
						}
						});
				}
				});

			auto coo_thread = std::thread([&]() {
				while (coo_rating.size() > 1) {
					remove_binaries(coo_rating, coo_bit_count, [](auto zero_count, auto one_count) {
						if (zero_count > one_count) {
							return '1';
						}
						else if (zero_count < one_count) {
							return '0';
						}
						else {
							return '0';
						}
						});
				}
				});

			oxygen_thread.join();
			coo_thread.join();
			return binary_string_to_int(oxygen_rating[0]) * binary_string_to_int(coo_rating[0]);
		}

	private:
		auto count_bits (auto binaries) {
			bit_count_t bit_count(binaries[0].length(), { 0,0 });
			for (int i = 0; i < binaries[0].length(); i++) {
				for (const auto& binary : binaries) {
					if (binary[i] == '0') {
						bit_count[i].first++;
					}
					else if (binary[i] == '1') {
						bit_count[i].second++;
					}
					else {
						std::cerr << "Invalid bit type " + binary[i] << std::endl;
						exit(EXIT_FAILURE);
					}
				}
			}
			return bit_count;
		}
		using individual_bit_count_t = std::pair<int, int>;
		using bit_count_t = std::vector<individual_bit_count_t>;
		std::vector<std::string> lines;
		std::vector<std::pair<int, int>> bit_count;
	};
} // solutions::day_3

#endif // DAY3_H