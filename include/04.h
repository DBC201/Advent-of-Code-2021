#ifndef DAY4_H
#define DAY4_H

#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <thread>
#include <barrier>
#include <00.h>

using solutions::day_0::Day0;
using utils::file_utils::get_lines;
using utils::string_utils::convert_string_vector;
using utils::string_utils::split_by_string;
using utils::string_utils::replace_substring;

namespace solutions::day_4 {
	const std::string day_id = "04";

	class Day4: public Day0 {
	public:
		Day4(std::string filepath): Day0(filepath) {
			lines = get_lines<std::string>(filepath, [](std::string line) {
				if (line[0] == ' ') {
					line = line.substr(1);
				}
				return replace_substring(line, "  ", " ");
				});

			numbers = convert_string_vector<int>(split_by_string(lines[0], ","));

			for (int i = 1; i < lines.size(); i++) {
				if (lines[i].empty()) {
					std::vector<std::string> table_data(5);
					for (int j = 1; j <= 5; j++) {
						table_data[j - 1] = lines[i + j];
					}
					tables.push_back(create_table(table_data));
					i += 5; // including i++
				}
			}
		}


		int part1() {
			auto part1_tables = tables;
			std::atomic<bool> won = false;
			std::barrier b(part1_tables.size());
			std::atomic<int> won_index = -1;
			std::atomic<int> winning_number = -1;

			std::vector<std::thread> threads(part1_tables.size());

			for (int i = 0; i < threads.size(); i++) {
				threads[i] = std::thread([&](int table_index) {
					int num_index = 0;
					while (!won && num_index < numbers.size()) {
						b.arrive_and_wait();
						bool win = mark_number(part1_tables[table_index], numbers[num_index]);
						if (win) {
							won_index = table_index;
							won = true;
							winning_number = numbers[num_index];
							break;
						}
						num_index++;
					}
					b.arrive_and_drop();
					}, i);
			}

			for (int i = 0; i < threads.size(); i++) {
				threads[i].join();
			}

			bingo_table_t winning_table = part1_tables[won_index];
			int sum = 0;
			for (const auto& row : winning_table) {
				for (const auto& num : row) {
					if (num != -1) {
						sum += num;
					}
				}
			}
			return sum * winning_number;
		}

		int part2() {
			auto part2_tables = tables;
			std::atomic<bool> won = false;
			std::barrier b(part2_tables.size());
			std::atomic<int> won_index = -1;
			std::atomic<int> winning_number = -1;

			std::vector<std::thread> threads(part2_tables.size());

			for (int i = 0; i < threads.size(); i++) {
				threads[i] = std::thread([&](int table_index) {
					int num_index = 0;
					while (num_index < numbers.size()) {
						b.arrive_and_wait();
						bool win = mark_number(part2_tables[table_index], numbers[num_index]);
						if (win) {
							won_index = table_index;
							won = true;
							winning_number = numbers[num_index];
							break;
						}
						num_index++;
					}
					b.arrive_and_drop();
					}, i);
			}

			for (int i = 0; i < threads.size(); i++) {
				threads[i].join();
			}

			bingo_table_t winning_table = part2_tables[won_index];
			int sum = 0;
			for (const auto& row : winning_table) {
				for (const auto& num : row) {
					if (num != -1) {
						sum += num;
					}
				}
			}
			return sum * winning_number;
		}

	private:
		std::vector<std::string> lines;
		std::vector<int> numbers;
		using bingo_table_t = std::vector<std::vector<int>>;
		std::vector<bingo_table_t> tables;
		bingo_table_t new_empty_table() {
			bingo_table_t t(5, std::vector<int>(5));
			return t;
		}

		bingo_table_t create_table(std::vector<std::string> table_data) {
			bingo_table_t new_table = new_empty_table();
			for (int i = 0; i < 5; i++) {
				auto row = convert_string_vector<int>(split_by_string(table_data[i], " "));
				new_table[i] = row;
			}
			return new_table;
		}

		bool mark_number(bingo_table_t& table, int number) {
			auto check_win_condition = [&](int i, int j) {
				bool row_match = true;
				bool column_match = true;
				for (int c = 0; c < 5; c++) {
					if (table[i][c] != -1) {
						row_match = false;
					}

					if (table[c][j] != -1) {
						column_match = false;
					}
				}
				return row_match || column_match;
			};
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (table[i][j] == number) {
						table[i][j] = -1;
						if (check_win_condition(i, j)) {
							return true;
						}
					}
				}
			}
			return false;
		}
	}; 
} // solutions::day_4`

#endif // DAY4_H