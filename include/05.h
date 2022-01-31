#ifndef DAY5_H
#define DAY5_H

#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <unordered_map>
#include <unordered_set>
#include <00.h>

using solutions::day_0::Day0;
using utils::string_utils::replace_substring;
using utils::string_utils::split_by_string;
using utils::string_utils::convert_string_vector;
using utils::file_utils::process_lines;

namespace solutions::day_5 {
	const std::string day_id = "05";

	class Day5 : public Day0 {
	public:
		Day5(std::string filepath) : Day0(filepath) {};

		int part1() {
			coords.clear();
			process_lines(
                filepath,
				coords,
				[&](std::string line, auto& overlaps) {
					auto coords = covering_coordinates(line);
					for (const auto& coord : coords) {
						if (overlaps.contains(coord)) {
							overlaps.at(coord)++;
						}
						else {
							overlaps.insert({ coord, 1 });
						}
					}
				});
			return count_overlaps(coords);
		}

		int part2() {
			coords.clear();
			process_lines(
                filepath,
				coords,
				[&](std::string line, auto& overlaps) {
					auto coords = covering_coordinates2(line);
					for (const auto& coord : coords) {
						if (overlaps.contains(coord)) {
							overlaps.at(coord)++;
						}
						else {
							overlaps.insert({ coord, 1 });
						}
					}
				});
			return count_overlaps(coords);
		}
	private:
		using overlap_map_t = std::unordered_map<std::string, int>;
		overlap_map_t coords;
		int count_overlaps(auto coords) {
			int overlap_count = 0;
			for (const auto& p : coords) {
				if (p.second > 1) {
					overlap_count++;
				}
			}
			return overlap_count;
		}

        std::vector<std::string> covering_coordinates(auto inp) {
            inp = replace_substring(inp, " ", "");
            auto tokens = split_by_string(inp, "->");
            auto c1 = convert_string_vector<int>(split_by_string(tokens[0], ","));
            auto c2 = convert_string_vector<int>(split_by_string(tokens[1], ","));
            std::unordered_set<std::string> all_coordinates;

            auto coord_to_string = [](auto coord) {
                return std::to_string(coord[0]) + ',' + std::to_string(coord[1]);
            };

            if (c1[1] == c2[1]) {
                all_coordinates.insert(coord_to_string(c1));
                all_coordinates.insert(coord_to_string(c2));
                if (c1[0] < c2[0]) {
                    while (c1[0] != c2[0]) {
                        c1[0]++;
                        all_coordinates.insert(coord_to_string(c1));
                    }
                }
                else {
                    while (c1[0] != c2[0]) {
                        c2[0]++;
                        all_coordinates.insert(coord_to_string(c2));
                    }
                }
            }
            else if (c1[0] == c2[0]) {
                all_coordinates.insert(coord_to_string(c1));
                all_coordinates.insert(coord_to_string(c2));
                if (c1[1] < c2[1]) {
                    while (c1[1] != c2[1]) {
                        c1[1]++;
                        all_coordinates.insert(coord_to_string(c1));
                    }
                }
                else {
                    while (c1[1] != c2[1]) {
                        c2[1]++;
                        all_coordinates.insert(coord_to_string(c2));
                    }
                }
            }

            std::vector<std::string> coords;
            std::copy(all_coordinates.begin(), all_coordinates.end(), std::back_inserter(coords));
            return coords;
        }

        std::vector<std::string> covering_coordinates2(auto inp) {
            inp = replace_substring(inp, " ", "");
            auto tokens = split_by_string(inp, "->");
            auto c1 = convert_string_vector<int>(split_by_string(tokens[0], ","));
            auto c2 = convert_string_vector<int>(split_by_string(tokens[1], ","));
            std::unordered_set<std::string> all_coordinates;

            auto coord_to_string = [](auto coord) {
                return std::to_string(coord[0]) + ',' + std::to_string(coord[1]);
            };

            float abs_slope = abs(((float)c2[1] - (float)c1[1]) / ((float)c2[0] - (float)c1[0]));

            if (c1[1] == c2[1]) {
                all_coordinates.insert(coord_to_string(c1));
                all_coordinates.insert(coord_to_string(c2));
                if (c1[0] < c2[0]) {
                    while (c1[0] != c2[0]) {
                        c1[0]++;
                        all_coordinates.insert(coord_to_string(c1));
                    }
                }
                else {
                    while (c1[0] != c2[0]) {
                        c2[0]++;
                        all_coordinates.insert(coord_to_string(c2));
                    }
                }
            }
            else if (c1[0] == c2[0]) {
                all_coordinates.insert(coord_to_string(c1));
                all_coordinates.insert(coord_to_string(c2));
                if (c1[1] < c2[1]) {
                    while (c1[1] != c2[1]) {
                        c1[1]++;
                        all_coordinates.insert(coord_to_string(c1));
                    }
                }
                else {
                    while (c1[1] != c2[1]) {
                        c2[1]++;
                        all_coordinates.insert(coord_to_string(c2));
                    }
                }
            }
            else if (abs_slope == 1) {
                all_coordinates.insert(coord_to_string(c1));
                all_coordinates.insert(coord_to_string(c2));
                while (c1[0] != c2[0] && c1[1] != c2[1]) {
                    // since we know for a fact that they have a abs slope of 1
                    // we don't have to check for equality
                    if (c1[0] < c2[0]) {
                        c1[0]++;
                    }
                    else {
                        c1[0]--;
                    }

                    if (c1[1] < c2[1]) {
                        c1[1]++;
                    }
                    else {
                        c1[1]--;
                    }
                    all_coordinates.insert(coord_to_string(c1));
                }
            }

            std::vector<std::string> coords;
            std::copy(all_coordinates.begin(), all_coordinates.end(), std::back_inserter(coords));
            return coords;
        }
	};
} // solutions::day_5

#endif // DAY5_H