#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Scores {
    public:
        Scores();
        void saveScores(int newScore);
        std::vector<int> getScores();

    private:
        std::vector<int> _scores;
        const std::string _file_path = "../src/scores/scores.txt";
};

#endif
