#pragma once
#include "board.h"
#include <vector>
#include "position.h"
#include <chrono>
#include <thread>
class Block {
public:
    Block();
    Block(int id, int rotate,std::vector<std::vector<int>> shape);
    std::vector<std::vector<Position>> cells;
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> getCellPoints();
    int id;
    int rotate;
    int rotation_control;
    void rotateClockwise();
    void rotateCounterClockwise();
    void setPosition(Position newPosition);
    Position getPosition();
    std::vector<std::vector<int>> shape_;
    int cellSize;
   
private:
    
    std::vector<Color> colors;
    
    Position position_;
};
