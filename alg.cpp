#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include "API.cpp"

const int ROWS = 16;
const int COLS = 16;

void floodFill() {
    
    int mazeWidth = API::mazeWidth();
    int mazeHeight = API::mazeHeight();

    std::vector<std::vector<int>> maze(ROWS, std::vector<int>(COLS, 0));

    const std::vector<std::pair<int, int>> moves = {
        std::make_pair(1, 0),
        std::make_pair(-1, 0),
        std::make_pair(0, 1),
        std::make_pair(0, -1)
    };

    std::queue<std::pair<int, int>> q;
    q.push({0, 1});

    while (!q.empty()) {
        auto [row, col] = q.front(); 
        q.pop();

        maze[row][col] = 2;

        bool hasWallFront = API::wallFront();
        bool hasWallRight = API::wallRight();
        bool hasWallLeft = API::wallLeft();

        if (!hasWallFront) {
            API::moveForward();
        }
        
        for (const auto& move : moves) {
            int newRow = row + move.first;
            int newCol = col + move.second;

            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && maze[newRow][newCol] == 0) {
                q.push({newRow, newCol});
            }
        }
    }
}

int main() {
    floodFill();
    return 0;
}