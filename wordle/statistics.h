#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#ifndef STATISTICS_H
#define STATISTICS_H

struct WordEntry {
    std::string word;
    int attempts;
    bool win;

    std::string getWin() {
        if (win) {
            return "Yes";
        }

        return "No";
    }
};

struct Stat {
    int timesPlayed;
    int avgAttempts;
    float winPercent;
    int curStreak;
    int longestStreak;
    std::vector<WordEntry> wEntries;
    
    Stat() {

    }

    Stat(int tPlayed, int avgAttempts, int winPercent, int curStreak, int longestStreak) {
        timesPlayed = tPlayed;
        this->avgAttempts = avgAttempts;
        this->curStreak = curStreak;
        this->longestStreak = longestStreak;
    }

    std::string toString(int lWidth) {
        std::stringstream ss;
        // First part of the output
        ss << std::setfill('=') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');
        ss << std::setfill(' ') << std::setw(4) << "" << std::setw(lWidth - 4) << "STATISTICS SUMMARY" << std::endl;
        ss << std::setfill('=') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');
        ss << std::setw(lWidth) << std::setfill(' ') << std::left << "Times Played:" << std::right << timesPlayed;
        ss << std::setw(lWidth) << std::setfill(' ') << std::left << "Average Attempts:" << std::right << avgAttempts;
        float winPerc = (float) (avgAttempts * 100) / timesPlayed; 
        ss << std::setw(lWidth) << std::setfill(' ') << std::left << "Win Percentage:" << std::right << std::setprecision(3) << winPerc << "%" << std::endl;
        ss << std::setw(lWidth) << std::setfill(' ') << std::left << "Current Streak:" << std::right << curStreak;
        ss << std::setw(lWidth) << std::setfill(' ') << std::left << "Longest Streak:" << std::right << longestStreak;

        ss << std::endl << std::endl;

        // Second part of the output
        ss << std::setfill('-') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');
        ss << std::setfill(' ') << std::setw(lWidth / 3) << std::left << "WORD" << std::setw(lWidth / 3) << std::left << "ATTEMPTS" << std::setw(lWidth / 3) << std::right << "WIN" << std::endl << std::setfill(' ');
        ss << std::setfill('-') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');

        // For each word guess, print out the attempt stats for the word
        for (auto& ws : wEntries) {
            ss << std::setw(lWidth / 3) << std::left << ws.word << std::setw(lWidth / 3) << std::right << ws.attempts << std::setw(lWidth / 3) << std::right << ws.getWin() << std::endl;
        }

        return ss.str();
    }

    void read() {
        std::ifstream ifs;
        ifs.open("statistics.txt");

        if (!ifs.is_open()) {
            return;
        }

        std::string statData;
        ifs >> statData;
        std::istringstream iss(statData);
        std::string line;
        while (std::getline(iss, line, '\n')) {
            std::istringstream lss(line);
            std::vector<std::string> values;
            std::string token;
            while (std::getline(lss, token, ',')) {
                values.push_back(token);
            }

            std::string category = values[0];
            if (category == "tPlayed") {
                timesPlayed = std::stoi(values[1]);
            } else if (category == "avgAttempts") {
                avgAttempts = std::stoi(values[1]);
            } else if (category == "winPercent") {
                winPercent = std::stof(values[1]);
            } else if (category == "curStreak") {
                curStreak = std::stoi(values[1]);
            } else if (category == "longStreak") {
                longestStreak = std::stoi(values[1]);
            } else if (category == "w") {
                WordEntry* w = new WordEntry;
                w->word = std::stoi(values[1]);
                w->attempts = std::stoi(values[2]);
                w->win = std::stoi(values[3]);
                wEntries.push_back(*w);
            }
        }

        ifs.close();
    }

    void save() {
        std::ofstream ofs;
        ofs.open("statistics.txt", std::fstream::trunc);
        ofs << "tPlayed" << "," << timesPlayed << std::endl;
        ofs << "avgAttempts" << "," << avgAttempts << std::endl;
        float winPerc = (float) (avgAttempts) / timesPlayed;
        ofs << "winPercent" << "," << std::setprecision(3) << winPerc << std::endl;
        ofs << "curStreak" << "," << curStreak << std::endl;
        ofs << "longStreak" << "," << longestStreak << std::endl;
        for (auto& v : wEntries) {
            ofs << "w" << "," << v.word << "," << v.attempts << "," << v.getWin() << std::endl;
        }

        ofs.close();
    }

    void reset() {
        std::ofstream ofs;
        ofs.open("stats.txt");
        ofs.close();
    }
};

#endif