#include <iostream>
#include <queue>
#include <unordered_map>
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
void floodFill(int startx, int starty,int endx,int endy, int prevC, int newC) {
    std::queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(startx, starty));


    // keep track of direction the rpobot is looking in using int variable
    //0=er schaut nach oben, 1=er schaut nach rechts, 2=erschaut nach unten, 3=er schaut nach links
    int direction = 0;
    
    //keep track of previous position
    int posX_prev = 0;
    int posY_prev = 0;

    API::setColor(startx, starty, newC);

    while (!queue.empty()) {
        std::pair<int, int> currentPixel = queue.front();
        queue.pop();

        int posX = currentPixel.first;
        int posY = currentPixel.second;

        API::setColor(posX, posY, newC);

        if(!(posX_prev==0 && posY_prev==0)){

            //Difference of coordinates 
            int diffx=posX-posX_prev;
            int diffy=posY-posY_prev;

            //This switch decides whether the robot can move to currentPixel and if yes the switch moves it
            switch (direction)
            {
            case 0:
                if(diffx==0 && diffy==1 && !API::wallFront()){
                    API::moveForward();
                }
                else if(diffx==1 && diffy==0 && !API::wallRight()){
                    API::turnRight();
                    API::moveForward();
                    direction=1;
                }
                else if(diffx==-1 && diffy==0 && !API::wallLeft()){
                    API::turnLeft();
                    API::moveForward();
                    direction=3;
                }
                else if(diffx==0 && diffy==-1){
                    API::turnRight();
                    API::turnRight();
                    API::moveForward();
                    direction=2;
                }
                break;
            case 1:
                if(diffx==1 && diffy==0 && !API::wallFront()){
                    API::moveForward();
                }
                else if(diffx==0 && diffy==-1 && !API::wallRight()){
                    API::turnRight();
                    API::moveForward();
                    direction=2;
                }
                else if(diffx==0 && diffy==1 && !API::wallLeft()){
                    API::turnLeft();
                    API::moveForward();
                    direction=0;
                }
                else if(diffx==-1 && diffy==0){
                    API::turnRight();
                    API::turnRight();
                    API::moveForward();
                    direction=3;
                }
                break;
            case 2:
                if(diffx==0 && diffy==-1 && !API::wallFront()){
                    API::moveForward();
                }
                else if(diffx==-1 && diffy==0 && !API::wallRight()){
                    API::turnRight();
                    API::moveForward();
                    direction=3;
                }
                else if(diffx==1 && diffy==0 && !API::wallLeft()){
                    API::turnLeft();
                    API::moveForward();
                    direction=1;
                }
                else if(diffx==0 && diffy==1){
                    API::turnRight();
                    API::turnRight();
                    API::moveForward();
                    direction=0;
                }
                break;
            case 3:
                if(diffx==-1 && diffy==0 && !API::wallFront()){
                    API::moveForward();
                }
                else if(diffx==0 && diffy==1 && !API::wallRight()){
                    API::turnRight();
                    API::moveForward();
                    direction=0;
                }
                else if(diffx==0 && diffy==-1 && !API::wallLeft()){
                    API::turnLeft();
                    API::moveForward();
                    direction=2;
                }
                else if(diffx==1 && diffy==0){
                    API::turnRight();
                    API::turnRight();
                    API::moveForward();
                    direction=1;
                }
                break;
            }
        }

        //check if end is reached
        if(currentPixel == std::make_pair(endx,endy)){
            API::setColor(endx, endy, newC);
            API::ackReset();
            std::cout << "Path found" << std::endl;
            return;
        }
        


        // check the neighbors
        // setcolor not necessary, I moved it to the top(s. line 63)
        if (isValid(posX + 1, posY, prevC, newC)) {
            //API::setColor(posX + 1, posY, newC);
            queue.push(std::make_pair(posX + 1, posY));
        }

        if (isValid(posX - 1, posY, prevC, newC)) {
            //API::setColor(posX - 1, posY, newC);
            queue.push(std::make_pair(posX - 1, posY));
        }

        if (isValid(posX, posY + 1, prevC, newC)) {
            //API::setColor(posX, posY + 1, newC);
            queue.push(std::make_pair(posX, posY + 1));
        }

        if (isValid(posX, posY - 1, prevC, newC)) {
            //API::setColor(posX, posY - 1, newC);
            queue.push(std::make_pair(posX, posY - 1));
        }

        posX_prev = posX;
        posY_prev = posY;
    }
}

int main() {
    
    int startX = 0, startY = 0;
    int prevC = API::getColor(startX, startY);
    int newC = 3;

    //Adjust the values accordingly
    int endX=15, endY=15;

    
    floodFill(startX, startY,endX,endY, prevC, newC);


    return 0;
}