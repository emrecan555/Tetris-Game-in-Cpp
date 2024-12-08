#pragma once
#include "board.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	Game(int numrows, int numcols);
	Board board;
	bool gameOver;
	Block GetRandomBLock();
	std::vector<Block> GetAllBlocks();
	void HandleInput();
	void MoveBlockDown();
	void MoveBlockLeft();
	void MoveBlockRight();
	void rotateBlockClockwise();
	void rotateBlockCounterClockwise();
	void HoldBlock();
	void Draw();
	double lastUpdateTime;
	bool EventTriggered(double interval);
	int score;
	int scorecontrol;
	int numrows;
	int numcols;
	int holdBlockCounter;
	std::vector<Block> Allblocks;
	std::vector<Block> blocks;
private:
	void LockBLock();
	void Reset();
	bool BlockFits();
	bool IsBlockOutside();
	void UpdateScore(int LinesCleared, int moveDownPoints);
	Block currentBlock;
	Block nextBlock;
	Block holdBlock;
	Sound rotateSound;
	Sound clearSound;
	Sound notRotateSound;
};