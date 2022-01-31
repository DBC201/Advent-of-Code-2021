#ifndef DAY14_H
#define DAY14_H

#include <00.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <unordered_map>

using utils::file_utils::process_lines;
using utils::string_utils::split_by_string;

using solutions::day_0::Day0;

namespace solutions::day_14 {
	const std::string day_id = "14";

	class Day14 : public Day0 {
	public:
		Day14(std::string filepath) : Day0(filepath) {
            process_lines(
                filepath,
                polymer_template,
                [](auto line, auto& polymer_template) {
                    auto tokens = split_by_string(line, " -> ");
                    if (tokens.size() == 1 && !tokens[0].empty()) {
                        polymer_template.insert({ "input", tokens[0] });
                    }
                    else {
                        polymer_template.insert({ tokens[0], tokens[1] });
                    }
                }
            );
		}

        auto part1() {
            int step_count = 10;
            auto input = polymer_template.at("input");
            for (int c = 0; c < step_count; c++) {
                for (int i = 1; i < input.length(); i++) {
                    auto curr_window = input.substr(i - 1, 2);
                    if (polymer_template.contains(curr_window)) {
                        input.insert(i, polymer_template.at(curr_window));
                        i++;
                    }
                }
            }

            std::unordered_map<char, int> letter_count;
            for (const auto& letter : input) {
                if (letter_count.contains(letter)) {
                    letter_count.at(letter)++;
                }
                else {
                    letter_count.insert({ letter, 1 });
                }
            }

            std::pair<char, int> max_count(NULL, INT_MIN);
            std::pair<char, int> min_count(NULL, INT_MAX);

            for (const auto& count : letter_count) {
                if (count.second > max_count.second) {
                    max_count = count;
                }
                if (count.second < min_count.second) {
                    min_count = count;
                }
            }
            return max_count.second - min_count.second;
        }

        auto part2() {
            int step_count = 40;
            auto input = polymer_template.at("input");
            std::unordered_map<std::string, uint_fast64_t> pair_count;

            for (int i = 1; i < input.length(); i++) {
                std::string curr_pair;
                curr_pair += input[i - 1];
                curr_pair += input[i];
                if (pair_count.contains(curr_pair)) {
                    pair_count.at(curr_pair)++;
                }
                else {
                    pair_count.insert({ curr_pair, 1 });
                }
            }

            std::unordered_map<char, uint_fast64_t> letter_count;

            for (const auto& letter : input) {
                if (letter_count.contains(letter)) {
                    letter_count.at(letter)++;
                }
                else {
                    letter_count.insert({ letter, 1 });
                }
            }

            for (int i = 0; i < step_count; i++) {
                std::unordered_map<std::string, uint_fast64_t> old_pair_count = pair_count;
                for (auto& p : old_pair_count) {
                    if (polymer_template.contains(p.first) && p.second > 0) {
                        std::string new_letter = polymer_template.at(p.first);
                        std::string new_pair1, new_pair2;
                        new_pair1 += p.first[0];
                        new_pair1 += new_letter;

                        new_pair2 += new_letter;
                        new_pair2 += p.first[1];

                        if (letter_count.contains(new_letter[0])) {
                            letter_count.at(new_letter[0]) += p.second;
                        }
                        else {
                            letter_count.insert({ new_letter[0], 1 });
                        }

                        if (pair_count.contains(new_pair1)) {
                            pair_count.at(new_pair1) += p.second;
                        }
                        else {
                            pair_count.insert({ new_pair1, p.second });
                        }

                        if (pair_count.contains(new_pair2)) {
                            pair_count.at(new_pair2) += p.second;
                        }
                        else {
                            pair_count.insert({ new_pair2, p.second });
                        }
                        pair_count.at(p.first) -= p.second;
                    }
                }
            }

            std::pair<char, uint_fast64_t> max_count(NULL, 0);
            std::pair<char, uint_fast64_t> min_count(NULL, UINT_FAST64_MAX);

            for (const auto& count : letter_count) {
                if (count.second > max_count.second) {
                    max_count = count;
                }
                if (count.second < min_count.second) {
                    min_count = count;
                }
            }
            return max_count.second - min_count.second;
        }
	private:
		using polymer_template_t = std::unordered_map<std::string, std::string>;
		polymer_template_t polymer_template;
	};

} // solutions::day_14

#endif // DAY14_H