#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include "colors.h"
class Board
{
public:
	Board();
	Board(int numrows, int numcols);
	void Initialize();
	void Draw();
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);
	int ClearFullRows();
	int numRows;
	int numCols;
	std::vector<std::vector<int>> board;
	int cellSize;
	void ShrinkBoard(int cancelledRows);
private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numrows);

	
	
	std::vector<Color> colors;
};