#include "board.h"

Board::Board()
{
}

Board::Board(int numrows, int numcols) :numRows(numrows),
numCols(numcols)
{
	cellSize = 30;
	Initialize();
	colors = GetCellColors();
}
void Board::Initialize()
{
	board.resize(numRows, std::vector<int>(numCols, 0));
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			board[row][column] = 0;
		}
	}
}


void Board::Draw()
{
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			int cellValue = board[row][column];
			DrawRectangle(column * cellSize + (320 - numCols * cellSize) /2 + 1, row * cellSize + (620 - numRows * cellSize) /2 + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
		}
	}
}
bool Board::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numCols)
	{
		return false;
	}
	return true;
}
bool Board::IsCellEmpty(int row, int column)
{
	if (board[row][column] == 0) return true;
	return false;
}

int Board::ClearFullRows()
{
	int completed = 0;
	for (int row = numRows - 1; row >= 0; row--)
	{
		if (IsRowFull(row))
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0) MoveRowDown(row, completed);
	}
	return completed;
}

bool Board::IsRowFull(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		if (board[row][column] == 0)
		{
			return false;
		}
	}
	return true;
}

void Board::ClearRow(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		board[row][column] = 0;
	}
}

void Board::MoveRowDown(int row, int numrows)
{
	for (int column = 0; column < numCols; column++)
	{
		board[row + numrows][column] = board[row][column];
		board[row][column] = 0;
	}
}
void Board::ShrinkBoard(int cancelledRows)
{
	int newRows = numRows - cancelledRows;
	int newCols = numCols;
	std::vector<std::vector<int>> newBoard(newRows, std::vector<int>(newCols, 0));
	for (int row = 0; row < newRows; row++)
	{
		for (int column = 0; column < newCols; column++)
		{
			newBoard[row][column] = board[row + 1][column];
		}
	}
	board = newBoard;
	numRows = newRows;
	numCols = newCols;
}
