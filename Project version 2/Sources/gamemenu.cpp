#include "gamemenu.h"



Gamemenu::Gamemenu()
{
}

Gamemenu::Gamemenu(int numrows, int numcols):numrows(numrows),numcols(numcols)
{
    game = Game(numrows,numcols);
    screenWidth=GetScreenWidth();
    resumeoffset=0;
    nameBuffer = "";
    isloadCustomPiecesactive=false;
    showStartMenu=true;
    isScoresActive=false;
    isTextBoxActive = false;
    isThemeActive = false;
    windowshouldclose = false;
    isFirstOpening = true;
    maxRotationCount = 1;
    theme = Themes();
    font = LoadFontEx("Fonts/ShortBaby-Mg2w.ttf", 64, 0, 0);
    blockmatrix.resize(4, std::vector<int>(4, 0));
    blockmatrix= { {0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
    gameLevel = 1;
}

void Gamemenu::scoredraw(vector<PlayerScore> scores)
{
    DrawText("Scoreboard", GetScreenWidth() / 2 - MeasureText("Scoreboard", 40) / 2, 20, 40, theme.textcolor);

    int yOffset = 80;
    for (int i = 0; i < scores.size() && i < 10; ++i) {
        DrawText(scores[i].name.c_str(), 75, yOffset, 30, theme.textcolor);
        DrawText(std::to_string(scores[i].score).c_str(), 300, yOffset, 30, theme.textcolor);
        yOffset += 40;
    }
    if (IsKeyDown(KEY_ENTER)) {
        showStartMenu = true;
        isScoresActive = false;
    }
}

void Gamemenu::textbox()
{
    DrawRectangle(float(screenWidth / 2 - 150), 70, 300, 80, theme.boxbackgroundcolor);
    DrawText("Enter Your Name:", screenWidth / 2 - MeasureText("Enter Your Name:", 20) / 2, 80, 20, theme.textcolor);
    DrawText(nameBuffer.c_str(), float((screenWidth - MeasureText(nameBuffer.c_str(), 20)) / 2), 120, 20, theme.textcolor);
    int key = GetKeyPressed();
    if (((key >= KEY_ZERO && key <= KEY_NINE) || (key == KEY_SPACE) || (key >= KEY_A && key <= KEY_Z)) && nameBuffer.length() <63) {
        nameBuffer += (char)key;
    }
    else if (key == KEY_BACKSPACE) {
        if (nameBuffer.length() > 0) {
            nameBuffer.pop_back();
        }
    }
    DrawRectangle(float(screenWidth / 2 - 150), 220, 300, 40, theme.boxbackgroundcolor);
    DrawText("Select Game Level", screenWidth / 2 - MeasureText("Enter Your Name:", 20) / 2, 230, 20, theme.textcolor);
    DrawRectangle(100, 295, 80, 40, theme.boxbackgroundcolor);
    DrawText("1", 140- MeasureText("1", 20) / 2, 305, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { 100, 295, 80, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameLevel = 1;
    }
    DrawRectangle(210, 295, 80, 40, theme.boxbackgroundcolor);
    DrawText("2", 250 - MeasureText("2", 20) / 2, 305, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { 210, 295, 80, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameLevel = 2;
    }
    DrawRectangle(320, 295, 80, 40, theme.boxbackgroundcolor);
    DrawText("3", 360 - MeasureText("3", 20) / 2, 305, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { 320, 295, 80, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameLevel = 3;
    }

    DrawRectangle(screenWidth / 2 - 150, 405, 300, 40, theme.boxbackgroundcolor);
    DrawText("Enter The Game", screenWidth / 2 - MeasureText("Enter The Game", 20) / 2, 415 , 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 150, 405 , 300, 40 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isTextBoxActive = false;
            playerName = nameBuffer;
            nameBuffer = "";
            game = Game(numrows, numcols);
            isFirstOpening = false;
        }

    DrawRectangle(screenWidth / 2 - 150, 515, 300, 40, theme.boxbackgroundcolor);
    DrawText("Load Custom Pieces", screenWidth / 2 - MeasureText("Load Custom Pieces", 20) / 2, 525, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 150, 515 , 300, 40 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        playerName = nameBuffer;
        isTextBoxActive = false;
        nameBuffer = "";
        isloadCustomPiecesactive = true;
    }
}

void Gamemenu::mainmenudraw()
{
    DrawText("Game Menu", screenWidth / 2 - MeasureText("Game Menu", 20) / 2, 60, 20, theme.textcolor);
    DrawRectangle(screenWidth / 2 - 80, 100, 160, 40, theme.boxbackgroundcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 80, 100, 160, 40 }))
    {
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            showStartMenu = false;
            isTextBoxActive = true;
        }

    }

    DrawText("New Game", screenWidth / 2 - MeasureText("New Game", 20) / 2, 110, 20, theme.textcolor);
    if (!isFirstOpening)
    {
        DrawRectangle(screenWidth / 2 - 80, 200, 160, 40, theme.boxbackgroundcolor);
        DrawText("Resume", screenWidth / 2 - MeasureText("Resume", 20) / 2, 210, 20, theme.textcolor);
        resumeoffset = 100;
        if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 80, 200, 160, 40 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                showStartMenu = false;
        } 
    }
    DrawRectangle(screenWidth / 2 - 80, 200 + resumeoffset, 160, 40, theme.boxbackgroundcolor);
    DrawText("Scores", screenWidth / 2 - MeasureText("Scores", 20) / 2, 210 + resumeoffset, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 80, 200 + resumeoffset, 160, 40 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showStartMenu = false;
            isScoresActive = true;
    }

    DrawRectangle(screenWidth / 2 - 80, 300 + resumeoffset, 160, 40, theme.boxbackgroundcolor);
    DrawText("Themes", screenWidth / 2 - MeasureText("Themes", 20) / 2, 310 + resumeoffset, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 80, 300 + resumeoffset, 160, 40 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            showStartMenu = false;
            isThemeActive = true;
    }
    DrawRectangle(screenWidth / 2 - 80, 400 + resumeoffset, 160, 40, theme.boxbackgroundcolor);
    DrawText("Exit", screenWidth / 2 - MeasureText("Exit", 20) / 2, 410 + resumeoffset, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 80, 400 + resumeoffset, 160, 40 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            windowshouldclose = true;
    }  
}

void Gamemenu::themes()
{   
    DrawRectangleRounded({ 35.25, 10, 437.5, 50 }, 0.3, 6, theme.boxbackgroundcolor);
    DrawText("BACKGROUND COLORS", screenWidth / 2 - MeasureText("BACKGROUND COLORS", 20) / 2, 25, 20, theme.textcolor);
    DrawRectangleLinesEx({ 31.25,70,125,125 }, 4, BLACK);
    DrawRectangle(35.25, 74, 117, 117, theme.backgroundColors[0]);
    if (CheckCollisionPointRec(GetMousePosition(), { 31.25,70,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyBackgroundcolor(0);
    }
    DrawRectangleLinesEx({ 187.5,70,125,125 }, 4, BLACK);
    DrawRectangle(191.5, 74, 117, 117, theme.backgroundColors[1]);
    if (CheckCollisionPointRec(GetMousePosition(), { 187.5,75,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyBackgroundcolor(1);
    }
    DrawRectangleLinesEx({ 343.75,70,125,125 }, 4, BLACK);
    DrawRectangle(348, 74, 117, 117, theme.backgroundColors[2]);
    if (CheckCollisionPointRec(GetMousePosition(), { 343.75,75,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyBackgroundcolor(2);
        }
    DrawRectangleRounded({ 35.25, 205, 437.5, 50 }, 0.3, 6, theme.boxbackgroundcolor);
    DrawText("TEXT COLORS", screenWidth / 2 - MeasureText("TEXT COLORS", 20) / 2, 220, 20, theme.textcolor);
    DrawRectangleLinesEx({ 31.25,265,125,125 }, 4, BLACK);
    DrawRectangle(35.25, 269, 117, 117, theme.textColors[0]);
    if (CheckCollisionPointRec(GetMousePosition(), { 31.25,265,125,125 })&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyTextcolor(0);
    }
    DrawRectangleLinesEx({ 187.5,265,125,125 }, 4, BLACK);
    DrawRectangle(191.5, 269, 117, 117, theme.textColors[1]);
    if (CheckCollisionPointRec(GetMousePosition(), { 187.5,265,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        theme.ApplyTextcolor(1);

    }
    DrawRectangleLinesEx({ 343.75,265,125,125 }, 4, BLACK);
    DrawRectangle(348, 269, 117, 117, theme.textColors[2]);
    if (CheckCollisionPointRec(GetMousePosition(), { 343.75,265,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyTextcolor(2);
    }
    DrawRectangleRounded({ 35.25, 400, 437.5, 50 }, 0.3, 6, theme.boxbackgroundcolor);
    DrawText("BOX BACKGROUND COLORS", screenWidth / 2 - MeasureText("BOX BACKGROUND COLORS", 20) / 2, 415, 20, theme.textcolor);
    DrawRectangleLinesEx({ 31.25,460,125,125 }, 4, BLACK);
    DrawRectangle(35.25, 464, 117, 117, theme.boxbackgroundColors[0]);
    if (CheckCollisionPointRec(GetMousePosition(), { 31.25,460,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyBoxBackgroundcolor(0);
    }
    DrawRectangleLinesEx({ 187.5,460,125,125 }, 4, BLACK);
    DrawRectangle(191.5, 464, 117, 117, theme.boxbackgroundColors[1]);
    if (CheckCollisionPointRec(GetMousePosition(), { 187.5,460,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyBoxBackgroundcolor(1);
    }
    DrawRectangleLinesEx({ 343.75,460,125,125 }, 4, BLACK);
    DrawRectangle(348, 464, 117, 117, theme.boxbackgroundColors[2]);
    if (CheckCollisionPointRec(GetMousePosition(), { 343.75,460,125,125 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            theme.ApplyBoxBackgroundcolor(2);
    }
    if (IsKeyPressed(KEY_ENTER)) {
        
        isThemeActive = false;
        showStartMenu = true;
    }
}

void Gamemenu::gameover()
{
    DrawTextEx(font, "GAME OVER", { (screenWidth - MeasureTextEx(font,"GAME OVER", 40,2).x) / 2, 64 }, 40,2, theme.textcolor);
    DrawTextEx(font, "Player Name", { (screenWidth - MeasureTextEx(font,"Player Name", 40,2).x) / 2, 168 }, 40, 2, theme.textcolor);
    DrawRectangleRounded({ 100, 272, 300, 60 }, 0.3, 6, theme.boxbackgroundcolor);
    DrawTextEx(font, (playerName).c_str(), {100+float((300 - MeasureTextEx(font, playerName.c_str(), 40, 2).x) / 2),282 }, 40, 2, theme.textcolor);
    DrawTextEx(font, "Player Score", { (screenWidth - MeasureTextEx(font,"Player Score", 40,2).x) / 2, 386 }, 40, 2, theme.textcolor);
    DrawRectangleRounded({ 100, 490, 300, 60 }, 0.3, 6, theme.boxbackgroundcolor);
    char scoreText[10];
    sprintf_s(scoreText, "%d", game.score);
    DrawTextEx(font, scoreText, {100+float(300 - MeasureTextEx(font, scoreText, 40, 2).x) / 2,500 }, 40, 2, theme.textcolor);
    if (IsKeyPressed(KEY_ENTER)) {
        SaveScore(playerName, game.score);
        isFirstOpening = true;
        resumeoffset = 0;
        game.gameOver = false;
        showStartMenu = true;
    }
}



void Gamemenu::loadCustomPieces()
{
    DrawRectangle(100, 50, 300, 30, theme.boxbackgroundcolor);
    DrawTextEx(font, "Select Max Rotation Count", { 100 + float((300 - MeasureTextEx(font, "Select Max Rotation Count", 20, 2).x) / 2), 55 }, 20, 2, theme.textcolor);
    DrawRectangle(100, 100, 60, 30, theme.boxbackgroundcolor);
    DrawTextEx(font, "1", { 100 + float((60 - MeasureTextEx(font, "1", 20, 2).x) / 2), 105 }, 20, 2, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { 100, 100, 60, 30 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            maxRotationCount = 1;
    }
    DrawRectangle(180, 100, 60, 30, theme.boxbackgroundcolor);
    DrawTextEx(font, "2", { 180 + float((60 - MeasureTextEx(font, "2", 20, 2).x) / 2), 105 }, 20, 2, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { 180, 100, 60, 30 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            maxRotationCount = 2;
    }
    DrawRectangle(260, 100, 60, 30, theme.boxbackgroundcolor);
    DrawTextEx(font, "3", { 260 + float((60 - MeasureTextEx(font, "3", 20, 2).x) / 2), 105 }, 20, 2, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { 260, 100, 60, 30 })&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            maxRotationCount = 3;
    }
    DrawRectangle(340, 100, 60, 30, theme.boxbackgroundcolor);
    DrawTextEx(font, "4", { 340 + float((60 - MeasureTextEx(font, "4", 20, 2).x) / 2), 105 }, 20, 2, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { 340, 100, 60, 30 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            maxRotationCount = 4;
    }
    DrawRectangle(100, 150, 300, 30, theme.boxbackgroundcolor);
    DrawTextEx(font, "Draw Your Piece", { 100 + float((300 - MeasureTextEx(font, "Draw Your Piece", 20, 2).x) / 2), 155 }, 20, 2, theme.textcolor);
    DrawMatrixRectangles();
    Block loadedBlock(11+loadedBlocks.size(), maxRotationCount, blockmatrix);
    Position currentPos = loadedBlock.getPosition();
    loadedBlock.setPosition({ 0,0 });
    loadedBlock.Draw(190,200);
    loadedBlock.setPosition(currentPos);
    DrawRectangle(screenWidth / 2 - 150, 350, 300, 40, theme.boxbackgroundcolor);
    DrawText("Load Custom Piece", screenWidth / 2 - MeasureText("Load Custom Piece", 20) / 2, 360, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 100, 350 , 200, 40 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!areMatricesEqual(loadedBlock.shape_, { {0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0} })) {
                loadedBlocks.push_back(loadedBlock);
                blockmatrix = { {0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
            }
            if (loadedBlocks.size() == 3) {
                isloadCustomPiecesactive = false;
                game = Game(numrows, numcols);
                for (int i = 0; i < loadedBlocks.size(); i++) {
                    game.Allblocks.push_back(loadedBlocks[i]);
                    game.blocks.push_back(loadedBlocks[i]);
                }
                isFirstOpening = false;
                loadedBlocks.clear();
            }
    }
    DrawRectangle(screenWidth / 2 - 150, 400, 300, 40, theme.boxbackgroundcolor);
    DrawText("Enter The Game", screenWidth / 2 - MeasureText("Enter The Game", 20) / 2, 410, 20, theme.textcolor);
    if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 100, 400 , 200, 40 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isloadCustomPiecesactive = false;
            if (!areMatricesEqual(loadedBlock.shape_, { {0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0} })) {
                loadedBlocks.push_back(loadedBlock);
                blockmatrix = { {0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
            }
            game = Game(numrows, numcols);
            for (int i = 0; i < loadedBlocks.size(); i++) {
                game.Allblocks.push_back(loadedBlocks[i]);
                game.blocks.push_back(loadedBlocks[i]);
            }
            loadedBlocks.clear();
            isFirstOpening = false;
    }
}

bool Gamemenu::areMatricesEqual(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2)
{
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        return false;  
    }

    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[0].size(); ++j) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }
    return true;
}


void Gamemenu::DrawMatrixRectangles() {
    int startX = 190;
    int startY = 200;
    int spacingX = 30;
    int spacingY = 30;

    for (int i = 0; i < blockmatrix.size(); i++) {
        for (int j = 0; j < blockmatrix[0].size(); j++) {
            DrawRectangle(startX + j * spacingX, startY + i * spacingY, 29, 29, theme.boxbackgroundcolor);

            if (CheckCollisionPointRec(GetMousePosition(), { float (startX + j * spacingX), float(startY + i * spacingY), 29, 29 })&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (blockmatrix[i][j] == 0) {
                        blockmatrix[i][j] = 1;
                    }
                    else {
                        blockmatrix[i][j] = 0;
                    }
            }
        }
    }
}