//
// Created by Vlad Isan on 05/12/2023.
//

#include "puzzle.h"

const std::unordered_map<char, RockType> rock_type_map{
        {'.', RockType::EMPTY},
        {'O', RockType::ROUND},
        {'#', RockType::CUBE}
};

const std::unordered_map<RockType, char> rock_type_map_reverse{
        {RockType::EMPTY, '.'},
        {RockType::ROUND, 'O'},
        {RockType::CUBE,  '#'}
};

int puzzle_sample_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_sample_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int puzzle_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int do_puzzle_1(std::ifstream &file) {
    std::string line;
    Grid grid{};

    while (std::getline(file, line)) {
        Row row{};

        for (const auto &c: line) {
            row.emplace_back(rock_type_map.at(c));
        }

        grid.emplace_back(row);
    }

    for (auto it = grid.begin(); it != grid.end(); ++it) {
        for (size_t j = 0; j < (*it).size(); ++j) {
            if ((*it)[j] == RockType::ROUND) {
                auto slide_to = it - 1;

                while (slide_to >= grid.begin() && (*slide_to)[j] == RockType::EMPTY) {
                    (*slide_to)[j] = RockType::ROUND;
                    slide_to[1][j] = RockType::EMPTY;

                    --slide_to;
                }
            }
        }
    }

    uint64_t sum = 0;

    for (size_t i = 0; i < grid.size(); ++i) {
        auto round_rocks = grid[i] | std::views::filter([](const auto &rock) { return rock == RockType::ROUND; });
        auto count = std::ranges::distance(round_rocks);

        sum += count * (grid.size() - i);
    }

    return sum;
}

int do_puzzle_2(std::ifstream &file) {
    std::string line;
    Grid grid{};

    while (std::getline(file, line)) {
        Row row{};

        for (const auto &c: line) {
            row.emplace_back(rock_type_map.at(c));
        }

        grid.emplace_back(row);
    }

    std::map<Grid, uint64_t> grid_map{};
    std::vector<int> sums{};

    for (uint64_t i = 0; i < CYCLES; ++i) {
        tilt_grid_north(grid, TiltDirection::NORTH);
        tilt_grid_west(grid, TiltDirection::WEST);
        tilt_grid_south(grid, TiltDirection::SOUTH);
        tilt_grid_east(grid, TiltDirection::EAST);

        uint64_t sum = 0;

        for (size_t i = 0; i < grid.size(); ++i) {
            auto round_rocks = grid[i] | std::views::filter([](const auto &rock) { return rock == RockType::ROUND; });
            auto count = std::ranges::distance(round_rocks);

            sum += count * (grid.size() - i);
        }

        sums.emplace_back(sum);

        if (grid_map.contains(grid)) {
            auto index = grid_map.at(grid);

            auto cycle = i - index;
            auto offset = index + 1;

            return sums[((CYCLES - offset) % cycle) + offset - 1];
        }

        grid_map[grid] = i;
    }
}

void tilt_grid_north(Grid &grid, TiltDirection direction) {
    for (auto it = grid.begin(); it != grid.end(); ++it) {
        for (size_t j = 0; j < (*it).size(); ++j) {
            if ((*it)[j] == RockType::ROUND) {
                auto slide_to = it - 1;

                while (slide_to >= grid.begin() && (*slide_to)[j] == RockType::EMPTY) {
                    (*slide_to)[j] = RockType::ROUND;
                    slide_to[1][j] = RockType::EMPTY;

                    --slide_to;
                }
            }
        }
    }
}

void tilt_grid_south(Grid &grid, TiltDirection direction) {
    for (auto it = grid.rbegin(); it != grid.rend(); ++it) {
        for (size_t j = 0; j < (*it).size(); ++j) {
            if ((*it)[j] == RockType::ROUND) {
                auto slide_to = it - 1;

                while (slide_to >= grid.rbegin() && (*slide_to)[j] == RockType::EMPTY) {
                    (*slide_to)[j] = RockType::ROUND;
                    slide_to[1][j] = RockType::EMPTY;

                    --slide_to;
                }
            }
        }
    }
}

void tilt_grid_west(Grid &grid, TiltDirection direction) {
    for (auto it = grid.begin(); it != grid.end(); ++it) {
        for (auto row_it = (*it).begin(); row_it < (*it).end(); ++row_it) {
            if (*row_it == RockType::ROUND) {
                auto slide_to = row_it - 1;

                while (slide_to >= (*it).begin() && *slide_to == RockType::EMPTY) {
                    *slide_to = RockType::ROUND;
                    slide_to[1] = RockType::EMPTY;

                    --slide_to;
                }
            }
        }
    }
}

void tilt_grid_east(Grid &grid, TiltDirection direction) {
    for (auto it = grid.begin(); it != grid.end(); ++it) {
        for (auto row_it = (*it).rbegin(); row_it < (*it).rend(); ++row_it) {
            if (*row_it == RockType::ROUND) {
                auto slide_to = row_it - 1;

                while (slide_to >= (*it).rbegin() && *slide_to == RockType::EMPTY) {
                    *slide_to = RockType::ROUND;
                    slide_to[1] = RockType::EMPTY;

                    --slide_to;
                }
            }
        }
    }
}
