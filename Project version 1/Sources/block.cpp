#include "block.h"
#include "colors.h"
#include <vector>
#include <iostream>







Block::Block()
{
}

Block::Block(int id,int rotate, std::vector<std::vector<int>> shape)
    : id(id), rotate(rotate), shape_(shape) {
    cellSize = 30;
    position_ = { 0,int((10 - shape_[0].size()) / 2)};
    colors = GetCellColors();
    rotation_control = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    for (std::size_t i = 0; i < shape_.size(); ++i) {
        for (std::size_t j = 0; j < shape_[0].size(); ++j) {
            if (shape_[i][j] != 0) {
                DrawRectangle((position_.column + j) * cellSize + offsetX, (position_.row + i) * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
            }
        }
    }
}

void Block::Move(int rows, int columns)
{
    position_.row += rows;
    position_.column += columns;
}

std::vector<Position> Block::getCellPoints() {
    std::vector<Position> cellPoints;

    for (std::size_t i = 0; i < shape_.size(); ++i) {
        for (std::size_t j = 0; j < shape_[0].size(); ++j) {
            if (shape_[i][j] != 0) {
                Position cellPoint(position_.row + i, position_.column+ j);
                cellPoints.push_back(cellPoint);
            }
        }
    }
    return cellPoints;
}
void Block::rotateClockwise() {
        std::vector<std::vector<int>> rotated(shape_[0].size(), std::vector<int>(shape_.size(), 0));

        for (std::size_t i = 0; i < shape_.size(); ++i) {
            for (std::size_t j = 0; j < shape_[0].size(); ++j) {
                rotated[j][shape_.size() - 1 - i] = shape_[i][j];
            }
        }
        shape_ = rotated;

}
void Block::rotateCounterClockwise() {
    std::vector<std::vector<int>> rotated(shape_.size(), std::vector<int>(shape_[0].size(), 0));

    for (std::size_t i = 0; i < shape_[0].size(); ++i) {
        for (std::size_t j = 0; j < shape_.size(); ++j) {
            rotated[j][i] = shape_[i][shape_[0].size() - 1 - j];
        }
    }

    shape_ = rotated;
}

void Block::setPosition(Position newPosition)
{
    position_ = newPosition;
}

Position Block::getPosition(){
    return position_;
}