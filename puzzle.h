//
// Created by Vlad Isan on 05/12/2023.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "fmt/core.h"

enum class RockType {
    EMPTY,
    ROUND,
    CUBE
};

enum class TiltDirection {
    NORTH,
    EAST,
    SOUTH,
    WEST
};


constexpr const uint64_t CYCLES = 1'000'000'000;
extern const std::unordered_map<char, RockType> rock_type_map;
extern const std::unordered_map<RockType, char> rock_type_map_reverse;

using Row = std::vector<RockType>;
using Grid = std::vector<Row>;

void tilt_grid_north(Grid &grid, TiltDirection direction);
void tilt_grid_south(Grid &grid, TiltDirection direction);
void tilt_grid_west(Grid &grid, TiltDirection direction);
void tilt_grid_east(Grid &grid, TiltDirection direction);

int puzzle_sample_1(const std::string &base_file_path);

int puzzle_sample_2(const std::string &base_file_path);

int puzzle_1(const std::string &base_file_path);

int puzzle_2(const std::string &base_file_path);

int do_puzzle_1(std::ifstream &file);

int do_puzzle_2(std::ifstream &file);

#endif //PUZZLE_H
