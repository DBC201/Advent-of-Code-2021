#ifndef DAY9_H
#define DAY9_H

#include <00.h>

#include <iostream>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <queue>

using utils::file_utils::get_lines;
using utils::string_utils::split_by_string;
using utils::string_utils::convert_string;

using solutions::day_0::Day0;

namespace solutions::day_9 {
	const std::string day_id = "09";

	class Day9 : public Day0 {
	public:
		Day9(std::string filepath) : Day0(filepath) {
			heightmap = get_lines<std::vector<uint32_t>>(filepath, [](auto line) {
				std::vector<uint32_t> values(line.length());
				for (int i = 0; i < line.length(); i++) {
					values[i] = convert_string<uint32_t>(line.substr(i, 1));
				}
				return values;
				});
		};

		auto part1() {
			uint32_t low_point_sum = 0;

			for (int i = 0; i < heightmap.size(); i++) {
				for (int j = 0; j < heightmap[i].size(); j++) {

					if (i - 1 >= 0 && heightmap[i - 1][j] <= heightmap[i][j]) {
						continue;
					}

					if (i + 1 < heightmap.size() && heightmap[i + 1][j] <= heightmap[i][j]) {
						continue;
					}

					if (j - 1 >= 0 && heightmap[i][j - 1] <= heightmap[i][j]) {
						continue;
					}

					if (j + 1 < heightmap[i].size() && heightmap[i][j + 1] <= heightmap[i][j]) {
						continue;
					}

					low_point_sum += heightmap[i][j] + 1;
				}
			}

			return low_point_sum;
		}

		auto part2() {
            std::vector<std::vector<bool>> visited(heightmap.size(), std::vector<bool>(heightmap[0].size(), false));

            auto basin_size = [&](int x, int y) {
                if (heightmap[y][x] == 9 || visited[y][x]) {
                    visited[y][x] = true;
                    return 0;
                }
                int visited_count = 0;
                visited[y][x] = true;

                std::queue<std::pair<int, int>> q;
                q.push({ x, y });
                while (!q.empty()) {
                    std::pair<int, int> curr = q.front();
                    q.pop();
                    visited_count++;

                    uint32_t curr_height = heightmap[curr.second][curr.first];

                    if (curr.second - 1 >= 0 &&
                        !visited[curr.second - 1][curr.first] && heightmap[curr.second - 1][curr.first] < 9) {
                        q.push({ curr.first, curr.second - 1 });
                        visited[curr.second - 1][curr.first] = true;
                    }

                    if (curr.second + 1 < heightmap.size() &&
                        !visited[curr.second + 1][curr.first] && heightmap[curr.second + 1][curr.first] < 9) {
                        q.push({ curr.first, curr.second + 1 });
                        visited[curr.second + 1][curr.first] = true;
                    }

                    if (curr.first - 1 >= 0 &&
                        !visited[curr.second][curr.first - 1] && heightmap[curr.second][curr.first - 1] < 9) {
                        q.push({ curr.first - 1, curr.second });
                        visited[curr.second][curr.first - 1] = true;
                    }

                    if (curr.first + 1 < heightmap[curr.second].size() &&
                        !visited[curr.second][curr.first + 1] && heightmap[curr.second][curr.first + 1] < 9) {
                        q.push({ curr.first + 1, curr.second });
                        visited[curr.second][curr.first + 1] = true;
                    }
                }
                return visited_count;
            };

            std::vector<int> basin_sizes;

            for (int y = 0; y < heightmap.size(); y++) {
                for (int x = 0; x < heightmap[y].size(); x++) {
                    basin_sizes.push_back(basin_size(x, y));
                }
            }

            std::sort(basin_sizes.begin(), basin_sizes.end(), [](auto a, auto b) { return a > b; });
            uint64_t result = (uint64_t)basin_sizes[0] * (uint64_t)basin_sizes[1] * (uint64_t)basin_sizes[2];

            return result;
		}

	private:
		std::vector<std::vector<uint32_t>> heightmap;
	};
} // solutions::day_9

#endif // DAY9_H