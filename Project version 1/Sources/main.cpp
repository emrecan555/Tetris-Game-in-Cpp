#include "gamemenu.h"

using namespace std;
const int screenWidth = 500;
const int screenHeight = 620;

int main() {    int numrows = 20;
    int numcols = 10;
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);
    InitAudioDevice();
    Music music = LoadMusicStream("Sounds/music.mp3");
    SetMusicVolume(music, 0.5);
    PlayMusicStream(music);
    Gamemenu gamemenu = Gamemenu(numrows,numcols);
    while (!gamemenu.windowshouldclose && WindowShouldClose() == false)
    {
        UpdateMusicStream(music);
        vector<PlayerScore> scores = LoadScores();
        BeginDrawing();
        ClearBackground(gamemenu.theme.backgroundcolor);
        if (gamemenu.showStartMenu)
        {
            gamemenu.mainmenudraw();
        }
        else if (gamemenu.isScoresActive) {
            gamemenu.scoredraw(scores);

        }
        else if (gamemenu.isTextBoxActive) {
            gamemenu.textbox();
        }
        else if (gamemenu.isloadCustomPiecesactive) {
            gamemenu.loadCustomPieces();
        }
        else if (gamemenu.isThemeActive) {
            gamemenu.themes();
        }
        else if (gamemenu.game.gameOver)
        {
            gamemenu.gameover();

        }
        else
        {
            gamemenu.game.HandleInput();
            if (gamemenu.game.EventTriggered(0.25-gamemenu.gameLevel*0.03)) gamemenu.game.MoveBlockDown();
            DrawTextEx(gamemenu.font, "Player Name", { 335,15 }, 24, 2, gamemenu.theme.textcolor);
            DrawRectangleRounded({ 320, 45, 170, 35 }, 0.3, 6, gamemenu.theme.boxbackgroundcolor);
            Vector2 playertextSize = MeasureTextEx(gamemenu.font, gamemenu.playerName.c_str(), 20, 2);
            DrawTextEx(gamemenu.font, (gamemenu.playerName).c_str(), { 320 + float((170 - playertextSize.x) / 2),57.5 }, 18, 2, gamemenu.theme.textcolor);
            DrawTextEx(gamemenu.font, "Score", { 365,95 }, 38, 2, gamemenu.theme.textcolor);
            DrawRectangleRounded({ 320, 135, 170, 60 }, 0.3, 6, gamemenu.theme.boxbackgroundcolor);
            DrawTextEx(gamemenu.font, "Next", { 370,210 }, 35, 2, gamemenu.theme.textcolor);
            DrawRectangleRounded({ 320, 250, 170, 150 }, 0.3, 6, gamemenu.theme.boxbackgroundcolor);
            if (gamemenu.game.holdBlockCounter == 1) {
                DrawTextEx(gamemenu.font, "Hold Block", { 330,415 }, 30, 2, gamemenu.theme.textcolor);
                DrawRectangleRounded({ 320, 455, 170, 150 }, 0.3, 6, gamemenu.theme.boxbackgroundcolor);
            }

            
            char scoreText[10];
            sprintf_s(scoreText, "%d", gamemenu.game.score);
            Vector2 textSize = MeasureTextEx(gamemenu.font, scoreText, 38, 2);
            DrawTextEx(gamemenu.font, scoreText, { 320 + (170 - textSize.x) / 2,145 }, 38, 2, gamemenu.theme.textcolor);
            
            gamemenu.game.Draw();
            if (IsKeyDown(KEY_SPACE)) {
                gamemenu.showStartMenu = true;
            }
        }
        EndDrawing();
    }
    UnloadMusicStream(music);
    CloseAudioDevice;
    CloseWindow();
    return 0;
}


