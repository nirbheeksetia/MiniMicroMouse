#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <algorithm>

// this file is irrelevant for the mms but the logic might be correct

const int ROWS = 16;
const int COLS = 16;

int maze[ROWS][COLS] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
};

// down, up, right, left
const std::vector<std::pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
        }
    };
}

// backtrack (returns the path)
std::vector<std::pair<int, int>> backtrack(std::unordered_map<std::pair<int, int>, std::pair<int, int>>& cameFrom, std::pair<int, int> start, std::pair<int, int> end) {
    std::vector<std::pair<int, int>> path;
    for (std::pair<int, int> at = end; at != start; at = cameFrom[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

// flood fill usinf BFS
std::vector<std::pair<int, int>> floodFill(int maze[ROWS][COLS], std::pair<int, int> start, std::pair<int, int> end) {
    std::queue<std::pair<int, int>> q;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>> cameFrom;
    q.push(start);
    cameFrom[start] = start;

    while (!q.empty()) {

        std::pair<int, int> cell = q.front();
        int row = cell.first;
        int col = cell.second;

        q.pop();

        // found
        if (std::make_pair(row, col) == end) {
            return backtrack(cameFrom, start, end);
        }

        // visited
        maze[row][col] = 2;

        // check all possible directions
        for (const auto& move : moves) {
            int newRow = row + move.first;
            int newCol = col + move.second;
            
            // check: not out of bounds, no wall, not visited
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && maze[newRow][newCol] == 0) {
                std::pair<int, int> neighbor = {newRow, newCol};
                if (cameFrom.find(neighbor) == cameFrom.end()) {
                    q.push(neighbor);
                    cameFrom[neighbor] = {row, col};
                }
            }
        }
    }

    return {}; // not found
}

int main() {
    std::pair<int, int> start = {0, 1};
    std::pair<int, int> end = {15, 14};

    std::vector<std::pair<int, int>> path = floodFill(maze, start, end);

    if (!path.empty()) {
        std::cout << "Path found:\n";
        for (const auto& [row, col] : path) {
            std::cout << "(" << row << ", " << col << ")\n";
        }
    } else {
        std::cout << "No path found\n";
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}