#include <iostream>
#include <queue>
#include <utility>
#include <tuple>
#include "API.h"
#include <string>

/* fun fact: API doesn't work here so we cannot actually test it :) 

inspired by https://www.geeksforgeeks.org/flood-fill-algorithm/

an example from github (mms) which doesn't work as well */

// void log(const std::string& text) {
//     std::cerr << text << std::endl;
// }

// int main() {
//     log("Running...");
//     API::setColor(0, 0, 'G');
//     API::setText(0, 0, "abc");
//     while (true) {
//         if (!API::wallLeft()) {
//             API::turnLeft();
//         }
//         while (API::wallFront()) {
//             API::turnRight();
//         }
//         API::moveForward();
//     }
// }


bool isValid(int x, int y, int prevC, int newC) {
    return (x >= 0 && x < API::mazeWidth() && y >= 0 && y < API::mazeHeight() &&
            API::getColor(x, y) == prevC && API::getColor(x, y) != newC);
}

// flood fill using BFS
void floodFill(int x, int y, int prevC, int newC) {
    std::queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(x, y));

    API::setColor(x, y, newC);

    while (!queue.empty()) {
        std::pair<int, int> currentPixel = queue.front();
        queue.pop();

        int posX = currentPixel.first;
        int posY = currentPixel.second;

        // check the neighbors
        if (isValid(posX + 1, posY, prevC, newC)) {
            API::setColor(posX + 1, posY, newC);
            queue.push(std::make_pair(posX + 1, posY));
        }

        if (isValid(posX - 1, posY, prevC, newC)) {
            API::setColor(posX - 1, posY, newC);
            queue.push(std::make_pair(posX - 1, posY));
        }

        if (isValid(posX, posY + 1, prevC, newC)) {
            API::setColor(posX, posY + 1, newC);
            queue.push(std::make_pair(posX, posY + 1));
        }

        if (isValid(posX, posY - 1, prevC, newC)) {
            API::setColor(posX, posY - 1, newC);
            queue.push(std::make_pair(posX, posY - 1));
        }
    }
}

int main() {
    
    int startX = 0, startY = 0;
    int prevC = API::getColor(startX, startY);
    int newC = 3;

    
    floodFill(startX, startY, prevC, newC);

    for (int x = 0; x < API::mazeWidth(); ++x) {
        for (int y = 0; y < API::mazeHeight(); ++y) {
            std::cout << API::getColor(x, y) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}