#ifndef DAY12_H
#define DAY12_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using utils::file_utils::process_lines;
using utils::string_utils::split_by_string;
using utils::string_utils::isLower;

using solutions::day_0::Day0;

namespace solutions::day_12 {
	const std::string day_id = "12";

	class Day12 : public Day0 {
	public:
		Day12(std::string filepath) : Day0(filepath) {
            process_lines(
                filepath,
                graph,
                [](auto line, graph_t& graph) {
                    auto tokens = split_by_string(line, "-");
                    if (graph.contains(tokens[0])) {
                        graph.at(tokens[0]).insert(tokens[1]);
                    }
                    else {
                        graph.insert({ tokens[0], edge_t({tokens[1]}) });
                    }

                    if (graph.contains(tokens[1])) {
                        graph.at(tokens[1]).insert(tokens[0]);
                    }
                    else {
                        graph.insert({ tokens[1], edge_t({tokens[0]}) });
                    }
                }
            );

            for (const auto& v : graph) {
                visited_count.insert({ v.first, 0 });
            }
		};

        int part1() {
            auto dfs = [](auto curr, auto visited_count, auto graph, auto&& dfs) {
                visited_count.at(curr)++;
                if (curr == "end") {
                    return 1;
                }
                else if (isLower(curr) && visited_count.at(curr) > 1) {
                    return 0;
                }

                int total_paths = 0;
                for (const auto& neighbor : graph.at(curr)) {
                    if (neighbor != "start") {
                        total_paths += dfs(neighbor, visited_count, graph, dfs);
                    }
                }

                return total_paths;
            };

            return dfs("start", visited_count, graph, dfs);
        }

        int part2() {
            auto dfs2 = [](auto curr, auto visited_count, auto graph, auto visited_small_twice, auto&& dfs2) {
                visited_count.at(curr)++;
                if (curr == "end") {
                    return 1;
                }
                else if (isLower(curr)) {
                    if (visited_small_twice && visited_count.at(curr) > 1) {
                        return 0;
                    }
                    else if (visited_count.at(curr) > 2) {
                        return 0;
                    }

                    if (visited_count.at(curr) == 2) {
                        visited_small_twice = true;
                    }
                }

                int total_paths = 0;
                for (const auto& neighbor : graph.at(curr)) {
                    if (neighbor != "start") {
                        total_paths += dfs2(neighbor, visited_count, graph, visited_small_twice, dfs2);
                    }
                }

                return total_paths;
            };

            return dfs2("start", visited_count, graph, false, dfs2);
        }
	private:
		using edge_t = std::unordered_set<std::string>;
		using graph_t = std::unordered_map<std::string, edge_t>;
		graph_t graph;
        std::unordered_map<std::string, int> visited_count;
	};
} // solutions::day_12

#endif // DAY12_H