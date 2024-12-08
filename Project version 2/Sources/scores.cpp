#include "scores.h"
using namespace std;


vector<PlayerScore> LoadScores() {
    vector<PlayerScore> scores;

    ifstream scoreFile("scores.txt");
    string line;

    while (getline(scoreFile, line)) {
        stringstream ss(line);
        PlayerScore playerScore;
        ss >> playerScore.name >> playerScore.score;
        scores.push_back(playerScore);
    }

    scoreFile.close();

    // Skorlarý sýrala (yüksekten düþüðe)
    sort(scores.begin(), scores.end(), [](const PlayerScore& a, const PlayerScore& b) {
        return a.score > b.score;
        });

    return scores;
}

void SaveScore(const string& playerName, int playerScore) {
    ofstream scoreFile("scores.txt", ios::app);
    scoreFile << playerName << " " << playerScore << endl;
    scoreFile.close();
}
