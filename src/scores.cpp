#include "scores.h"
#include <algorithm>

Scores::Scores() {

}

void Scores::saveScores(int newScore) {
    std::ofstream write_file;

    write_file.open(_file_path, std::ios::out | std::ios::app);
    if (write_file.is_open())
    {
        write_file << std::to_string(newScore) << std::endl;
        write_file.close();
    }
}

std::vector<int> Scores::getScores() {
    std::ifstream read_file;
    std::string line;

    read_file.open(_file_path);
    if (read_file.is_open())
    {
        while (std::getline(read_file,line))
        {
            _scores.push_back(std::stoi(line));
        }
        read_file.close();
    }

    std::sort(_scores.begin(), _scores.end());

    return _scores;
}