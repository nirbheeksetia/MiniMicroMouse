#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

//maze
const int ROWS = 10;
const int COLS = 10;

//1 wall, 0 path)
int maze[ROWS][COLS] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}
};

//down, up, right, left
const std::vector<std::pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

//flood fill
void floodFill(int maze[ROWS][COLS], int startRow, int startCol) {
    
    //start
    std::queue<std::pair<int, int>> q;
    q.push({startRow, startCol});
    
    //find path using BFS
    while (!q.empty()) {
        auto [row, col] = q.front(); 
        q.pop();

        //visited
        maze[row][col] = 2;

        //possible directions
        for (const auto& move : moves) {
            int newRow = row + move.first;
            int newCol = col + move.second;

            //validation
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && maze[newRow][newCol] == 0) {
                //step
                q.push({newRow, newCol});
            }
        }
    }
}

int main() {
    
    floodFill(maze, 0, 1);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}