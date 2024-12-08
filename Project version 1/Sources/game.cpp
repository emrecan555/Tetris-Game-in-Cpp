#include "game.h"
#include <random>

Game::Game()
{
}

Game::Game(int numrows,int numcols)
{
	numrows = numrows; 
	numcols = numcols;
	board = Board(numrows,numcols);
	Allblocks.resize(10);
	Allblocks = tetrisBlocks;
	blocks = GetAllBlocks();
	currentBlock = GetRandomBLock();
	nextBlock = GetRandomBLock();
	gameOver = false;
	lastUpdateTime = 0;
	score = 0;
	scorecontrol = 0;
	holdBlockCounter = 0;
	rotateSound = LoadSound("Sounds/rotate.mp3");
	notRotateSound= LoadSound("Sounds/notRotate.mp3");
	clearSound = LoadSound("Sounds/clear.mp3");
}


Block Game::GetRandomBLock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}
std::vector<Block> Game::GetAllBlocks()
{
	return Allblocks;
}
void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0)
	{
		gameOver = false;
		Reset();
	}
	switch (keyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		UpdateScore(0, 1);
		break;

	case KEY_Q:
		rotateBlockClockwise();
		break;
	case KEY_E:
		rotateBlockCounterClockwise();
		break;

	case KEY_H:
		HoldBlock();
		break;
	}
}

void Game::MoveBlockDown()
{
	if (!gameOver) {
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(-1, 0);
			LockBLock();
		}
	}
}
void Game::MoveBlockLeft()
{
	if (!gameOver) {
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, 1);
		}
	}
}
void Game::MoveBlockRight()
{
	if (!gameOver) {
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, -1);
		}
	}
}
void Game::rotateBlockClockwise()
{
	if (!gameOver&& currentBlock.rotation_control<currentBlock.rotate) {
		currentBlock.rotateClockwise();
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.rotateCounterClockwise();
			PlaySound(notRotateSound);
		}
		else {
			PlaySound(rotateSound);
			currentBlock.rotation_control++;
		}
	}
	else {
		PlaySound(notRotateSound);
	}
}
void Game::rotateBlockCounterClockwise()
{
	if (!gameOver && currentBlock.rotation_control < currentBlock.rotate) {
		currentBlock.rotateCounterClockwise();
		if (IsBlockOutside() || BlockFits() == false) {
			currentBlock.rotateClockwise();
			PlaySound(notRotateSound);
		}
		else {
			PlaySound(rotateSound);
			currentBlock.rotation_control++;
		}
	}
	else {
		PlaySound(notRotateSound);
	}
}
void Game::Draw()
{
	board.Draw();
	currentBlock.Draw((320 - board.numCols * board.cellSize) / 2 + 1, (620 - board.numRows * board.cellSize) / 2 + 1);
	Position currentPos = nextBlock.getPosition();
	nextBlock.setPosition({ 0,0 });
	nextBlock.Draw(320+(170-nextBlock.shape_.size()*nextBlock.cellSize)/2, 250+ (150 - nextBlock.shape_[0].size() * nextBlock.cellSize) / 2);
	nextBlock.setPosition(currentPos);
	if (holdBlockCounter == 1) {
		holdBlock.Draw(270, 510);
	}

	
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.getCellPoints();
	for (Position item : tiles)
	{
		if (board.IsCellOutside(item.row, item.column))
		{
			return true;
		}
	}
	return false;
}

void Game::LockBLock()
{
	std::vector<Position> tiles = currentBlock.getCellPoints();
	for (Position item : tiles)
	{
		board.board[item.row][item.column] =currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}
	nextBlock = GetRandomBLock();
	int rowsCleared= board.ClearFullRows();
	if (rowsCleared > 0) {
		PlaySound(clearSound);
		UpdateScore(rowsCleared, 0);
	}
	
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.getCellPoints();
	for (Position item : tiles)
	{
		if (board.IsCellEmpty(item.row, item.column) == false)
		{
			return false;
		}
	}
	return true;
}

void Game::Reset()
{
	board.Initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBLock();
	nextBlock = GetRandomBLock();
	score = 0;
}



void Game::UpdateScore(int LinesCleared, int moveDownPoints)
{
	if(LinesCleared>5)
	{
		score += LinesCleared * 300;
	}
	else if (LinesCleared >= 3) {
		score += LinesCleared * 200;
	}
	else {
		score += LinesCleared * 100;
	}
	
	score += moveDownPoints;
	if (score <= 1200 && score - scorecontrol >= 300) 
	{
		board.ShrinkBoard(int((score - scorecontrol) / 300));
		scorecontrol = score;
		
	}
}


bool Game::EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

void Game::HoldBlock()
{
	if (!gameOver) {
		if (holdBlockCounter <1)
		{
			holdBlock = nextBlock;
			nextBlock = GetRandomBLock();
			holdBlockCounter++;
		}
		else if(holdBlockCounter==1)
		{
			nextBlock = holdBlock;
			holdBlockCounter++;
		}
	}	
}

