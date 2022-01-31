#ifndef DAY2_H
#define DAY2_H

#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <00.h>

using utils::file_utils::process_lines;
using utils::string_utils::split_by_string;
using solutions::day_0::Day0;

namespace solutions::day_2 {
	const std::string day_id = "02";

	class Day2: public Day0 {
	public:

		Day2(std::string filepath) : Day0(filepath) {};

		int part1() {
			std::pair<int, int> final_pos(0, 0);

			process_lines(
				filepath,
				final_pos,
				[](std::string line, std::pair<int, int>& prev) {
					auto tokens = split_by_string(line, " ");
					std::string dir = tokens[0];
					int disposition = stoi(tokens[1]);
					if (dir == "forward") {
						prev.first += disposition;
					}
					else if (dir == "up") {
						prev.second -= disposition;
					}
					else if (dir == "down") {
						prev.second += disposition;
					}
					else {
						std::cerr << "invalid direction " + dir << std::endl;
						exit(EXIT_FAILURE);
					}
				}
			);

			return final_pos.first * final_pos.second;
		}

		int part2() {
			std::vector<int> final_pos_with_aim(3, 0);

			process_lines(
				filepath,
				final_pos_with_aim,
				[](std::string line, std::vector<int>& pos) {
					auto tokens = split_by_string(line, " ");
					std::string dir = tokens[0];
					int disposition = stoi(tokens[1]);
					if (dir == "forward") {
						pos[0] += disposition;
						pos[1] += disposition * pos[2];
					}
					else if (dir == "up") {
						pos[2] -= disposition;
					}
					else if (dir == "down") {
						pos[2] += disposition;
					}
					else {
						std::cerr << "invalid direction " + dir << std::endl;
						exit(EXIT_FAILURE);
					}
				}
			);

			return final_pos_with_aim[0] * final_pos_with_aim[1];
		}
	};
} // solutions::day_2

#endif // DAY2_H