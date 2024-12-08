#pragma once
#include <iostream>
#include "game.h"
#include "Themes.h"
#include "scores.h"

class Gamemenu{
public:
	Gamemenu();
	Gamemenu(int numrows,int numcols);
	void scoredraw( vector<PlayerScore> scores);
	void textbox();
	void mainmenudraw();
	void themes();
	void gameover();
	void loadCustomPieces();
	float screenWidth;
	float resumeoffset;
	bool isloadCustomPiecesactive;
	bool isFirstOpening;
	bool isScoresActive;
	bool showStartMenu;
	bool isTextBoxActive;
	bool isThemeActive;
	bool windowshouldclose;
	bool areMatricesEqual(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2);
	void DrawMatrixRectangles();
	int gameLevel;
	Font font;
	string nameBuffer;
	string playerName;
	Game game;
	Themes theme;
	std::vector<std::vector<int>> blockmatrix;
	std::vector<Block> loadedBlocks;
	Block loadedBlock;
	int maxRotationCount;
private:
	int numrows;
	int numcols;
};