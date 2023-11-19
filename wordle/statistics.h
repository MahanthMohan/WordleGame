#include <string>
#include <ostream>
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

    WordEntry() {
        word = "";
        attempts = 0;
        win = false;
    }

    WordEntry(std::string word, int attempts, bool win) {
        this->word = word;
        this->attempts = attempts;
        this->win = win;
    }

    std::string getWin() {
        if (win) {
            return "Yes";
        }

        return "No";
    }
};

struct Stat {    
    public:
        int timesPlayed;
        int wins;
        int curStreak;
        int longestStreak;
        std::vector<WordEntry> wEntries;
    
    Stat() {
        timesPlayed = 0;
        wins = 0;
        curStreak = 0;
        longestStreak = 0;
        wEntries = *(new std::vector<WordEntry>());
    }

    void display(std::ostream& os, int lWidth) {
        // First part of the output
        os << std::setfill('=') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');
        os << std::setfill(' ') << std::setw(4) << "" << std::setw(lWidth - 4) << "STATISTICS SUMMARY" << std::endl;
        os << std::setfill('=') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');
        os << std::setw(14) << std::setfill(' ') << std::left << "Times Played:" << std::setw(lWidth - 14) << std::right << timesPlayed << std::endl;

        int sumAttempts = 0;
        for (auto& e : wEntries) {
            sumAttempts += e.attempts;
        }

        int avgAttempts = sumAttempts / wEntries.size();

        os << std::setw(18) << std::setfill(' ') << std::left << "Average Attempts:" << std::setw(lWidth - 18) << std::right << avgAttempts << std::endl;
        float winPerc = ((float) wins * 100) / wEntries.size();
        os << std::setw(16) << std::setfill(' ') << std::left << "Current Streak:" << std::setw(lWidth - 16) << std::right << curStreak << std::endl;
        os << std::setw(16) << std::setfill(' ') << std::left << "Longest Streak:" << std::setw(lWidth - 16) << std::right << longestStreak << std::endl;

        os << std::endl << std::endl;

        // Second part of the output
        os << std::setfill('-') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');
        os << std::setfill(' ') << std::setw(lWidth / 3) << std::left << "WORD" << std::setw(lWidth / 3) << std::left << "ATTEMPTS" << std::setw(lWidth / 3) << std::right << "WIN" << std::endl << std::setfill(' ');
        os << std::setfill('-') << std::setw(lWidth) << "" << std::endl << std::setfill(' ');

        // For each word guess, print out the attempt stats for the word
        for (auto& ws : wEntries) {
            os << std::setw(lWidth / 3) << std::left << ws.word << std::setw(lWidth / 3) << std::right << ws.attempts << std::setw(lWidth / 3) << std::right << ws.getWin() << std::endl;
        }
    }

    void read() {
        std::ifstream ifs;
        ifs.open("statistics.txt");

        if (!ifs.is_open()) {
            return;
        }

        std::string statData;
        ifs >> statData;

        std::istringstream ios(statData);
        std::string line;
        while (std::getline(ios, line, '\n')) {
            std::istringstream los(line);
            std::vector<std::string> values;
            std::string token;
            while (std::getline(los, token, ',')) {
                values.push_back(token);
            }

            std::string category = values[0];
            if (category == "tPlayed") {
                timesPlayed = std::stoi(values[1]);
            } else if (category == "wins") {
                wins = std::stoi(values[1]);
            } else if (category == "curStreak") {
                curStreak = std::stoi(values[1]);
            } else if (category == "longStreak") {
                longestStreak = std::stoi(values[1]);
            } else if (category == "w") {
                std::string word = values[1];
                int attempts = std::stoi(values[2]);
                bool win = (bool) std::stoi(values[3]);
                WordEntry* w = new WordEntry(word, attempts, win);
                wEntries.push_back(*w);
            }
        }

        ifs.close();
    }

    void save() {
        std::ofstream ofs;
        ofs.open("statistics.txt", std::fstream::trunc);
        ofs << "tPlayed" << "," << timesPlayed << std::endl;
        ofs << "wins" << "," << wins << std::endl;
        ofs << "curStreak" << "," << curStreak << std::endl;
        ofs << "longStreak" << "," << longestStreak << std::endl;
        for (auto& v : wEntries) {
            ofs << "w" << "," << v.word << "," << v.attempts << "," << v.getWin() << std::endl;
        }

        ofs.close();
    }

    void reset() {
        std::ofstream ofs;
        ofs.open("statistics.txt");
        ofs << "tPlayed" << "," << 0 << std::endl;
        ofs << "wins" << "," << 0 << std::endl;
        ofs << "curStreak" << "," << 0 << std::endl;
        ofs << "longStreak" << "," << 0 << std::endl;
        ofs.close();
        curStreak = 0;
        longestStreak = 0;
        timesPlayed = 0;
        wins = 0;
        wEntries.clear();
    }
};

#endif