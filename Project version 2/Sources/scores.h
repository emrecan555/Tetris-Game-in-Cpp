#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "raylib.h"
using namespace std;

struct PlayerScore {
    string name;
    int score;
};

vector<PlayerScore> LoadScores();
void SaveScore(const string& playerName, int playerScore);