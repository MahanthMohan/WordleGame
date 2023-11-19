#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include "display.h"
#define WHITE 1
#define YELLOW 2
#define GREEN 3
#define GRAY 4
#define RESET 0
#define VALID_WORDS_FILE "words.txt"
#define VALID_GUESSES_FILE "allowed.txt"

#ifndef WORDLE_H
#define WORDLE_H

int binarySearch(std::vector<std::string> validWords, std::string target) {
    int left = 0;
    int right = validWords.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (validWords[mid] == target) {
            return mid;
        } else if (validWords[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return -1;
}

bool checkWin(std::string wordle, std::string guess) {
    return wordle == guess;
}

bool checkValidGuess(std::vector<std::string> validGuesses, std::vector<std::string> words, std::string guess) {
    if (guess.length() != 5) {
        return false;
    }

    int idx1 = binarySearch(validGuesses, guess);
    int idx2 = binarySearch(words, guess);
    return idx1 != -1 || idx2 != -1;
}

// main algorithm for coloring the guess made, based on the chosen wordle
std::vector<int> highlightGuess(std::string guess, std::string chosenWordle) {
    std::vector<int> colors;
    for (size_t i = 0; i < guess.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < chosenWordle.size() && !found; j++) {
            if (guess[i] == chosenWordle[j]) {
                if (i == j) {
                    colors.push_back(GREEN);
                } else {
                    colors.push_back(YELLOW);
                }

                found = true;
            }
        }

        // If the character is not found, highlight the char gray
        if (!found) {
            colors.push_back(GRAY);
        }
    }
    
    return colors;
}

// Samples a random word from the words list, in buckets
// and then returns a random word from the chosen list.
std::string genWordle(std::vector<std::string> wordList, int n) {
    int len = wordList.size();
    int sampleSize = len / n;
    std::vector<std::string> randWords;
    for (int i = 0; i < n; i++) {
        int r = rand() % n;
        randWords.push_back(wordList[r]);
    }

    int selectRandIdx = randWords.size() / 2;
    return randWords[selectRandIdx];
}

void loadWords(std::vector<std::string>& words, std::vector<std::string>& allowed) {
    std::ifstream ifs1;
    ifs1.open(VALID_WORDS_FILE);

    if (!ifs1.is_open()) {
        return;
    }

    std::string wd;
    while (std::getline(ifs1, wd, '\n')) {
        words.push_back(wd);
    }

    ifs1.close();

    std::ifstream ifs2;
    ifs2.open(VALID_GUESSES_FILE);
    if (!ifs2.is_open()) {
        return;
    }

    while (std::getline(ifs2, wd, '\n')) {
        allowed.push_back(wd);
    }

    ifs2.close();
}

void writeOutput(std::string guess, std::vector<int> colors) {
    std::ofstream ofs;
    ofs.open("interface.txt", std::ofstream::trunc);

    if (!ofs.is_open()) {
        return;
    }

    for (int i = 0; i < 5; i++) {
        ofs << guess[i] << "," << colors[i] << std::endl;    
    }

    ofs.close();
}

#endif