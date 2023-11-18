#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "statistics.h"
#define LINE_WIDTH_1 26
#define LINE_WIDTH_2 46
#define WHITE 1
#define YELLOW 2
#define GREEN 3
#define GRAY 4
#define RESET 0
#define WHITE_CODE "\033[0;37m"
#define YELLOW_CODE "\033[0;33m"
#define GREEN_CODE "\033[0;32m"
#define RESET_CODE "\033[0m"
#define GRAY_CODE "\033[0;90m"
#define BOLD_ON_CODE "\e[1m"
#define BOLD_RESET "\e[0m"
#define RANDOM_NUM_BUCKETS 7

std::string getColor(int color) {
    if (color == WHITE) {
        return WHITE_CODE;
    } else if (color == YELLOW) {
        return YELLOW_CODE;
    } else if (color == GREEN) {
        return GREEN_CODE;
    } else if (color == GRAY) {
        return GRAY_CODE; 
    } else if (color == RESET) {
        return RESET_CODE;
    }

    return WHITE_CODE;
}

void displayGuess(std::ostream& os, std::string guess, std::vector<int> colors) {
    if (guess.length() != colors.size()) {
        os << "Error: length of guess != number of colors" << std::endl;
        return;
    }

    os << std::setfill(' ');
    // Upper part
    for (int i = 0; i < guess.length(); i++) {
        os << std::setw(1) << "";
        std::string color_code = getColor(colors[i]);
        os << color_code << std::setfill('-') << std::setw(3) << "" << RESET_CODE << std::setfill(' ');
        os << std::setw(1) << "";
    }

    os << std::endl;

    // Letter part
    for (int i = 0; i < guess.length(); i++) {
        std::string color_code = getColor(colors[i]);
        os << color_code << "|" << std::setw(1) << "" << std::setw(2) << guess[i] << "" << "|" << RESET_CODE;
    }

    os << std::endl;

    // Lower part
    for (int i = 0; i < guess.length(); i++) {
        os << std::setw(1) << "";
        std::string color_code = getColor(colors[i]);
        os << color_code << std::setfill('-') << std::setw(3) << "" << RESET_CODE << std::setfill(' ');
        os << std::setw(1) << "";
    }

    os << std::endl;
}

void instrMenu(std::ostream& os, std::istream& is) {
    os << std::setfill('=') << std::setw(LINE_WIDTH_2) << "" << std::endl;
    os << std::setfill(' ') << std::setw(18) << "" << std::setw(LINE_WIDTH_2 - 18) << "HOW TO PLAY" << std::endl; 
    os << std::setfill('=') << std::setw(LINE_WIDTH_2) << "" << std::endl << std::setfill(' ');
    os << std::setw(LINE_WIDTH_2) << "Guess the Wordle in 6 tries." << std::endl;
    os << std::endl;
    os << std::endl;
    os << "HOW TO PLAY:" << std::endl;
    os << "- Each guess must be a valid 5 letter word." << std::endl;
    os << "- The color of the tiles will change to show" << std::endl;
    os << std::setw(2) << "" << std::setw(LINE_WIDTH_2 - 2) << "you how close your guess was to the word." << std::endl;
    os << std::endl;
    os << std::endl;
    displayGuess(os, "WEARY", {GREEN, WHITE, WHITE, WHITE, WHITE});
    os << BOLD_ON_CODE << "W" << BOLD_RESET << " is in the word and in the correct spot." << std::endl;
    os << std::endl;
    displayGuess(os, "PILLS", {WHITE, YELLOW, WHITE, WHITE, WHITE});
    os << BOLD_ON_CODE << "I" << BOLD_RESET << " is in the word but in the wrong spot." << std::endl;
    os << std::endl;
    displayGuess(os, "VAGUE", {WHITE, WHITE, WHITE, GRAY, WHITE});
    os << BOLD_ON_CODE << "U" << BOLD_RESET << " is not in the word in any spot." << std::endl;
    os << std::endl;
    os << std::endl;
    enterKeyEvent(is, os);
}

void enterKeyEvent(std::istream& is, std::ostream& os) {
    os << "Press [enter] to continue" << std::endl;
    std::string input;
    bool isEmpty = false;
    while (!isEmpty) {
        std::getline(std::cin, input);
        if (input.length() == 0) {
            isEmpty = true;
        }
    }
} 

int optionMenu(std::ostream& os, std::istream& is) {
    os << std::setfill('=') << std::setw(LINE_WIDTH_1) << "" << std::endl << std::setfill(' ');
    os << std::setw(4) << "" << std::setw(LINE_WIDTH_1 - 4) << std::left << "WELCOME TO WORDLE" << std::endl;
    os << std::setfill('=') << std::setw(LINE_WIDTH_1) << "" << std::endl << std::setfill(' ');

    os << "1. Play Wordle" << std::endl;
    os << "2. How to Play" << std::endl;
    os << "3. Statistics Summary" << std::endl;
    os << "4. Reset Statistics" << std::endl;
    os << "5. Exit" << std::endl;
    os << std::endl;
    os << std::endl;
 
    std::cout << "Select an option: " << std::endl;
    std::string opt_str;
    std::getline(is, opt_str);
    int opt = std::stoi(opt_str);
    return opt;
}

std::string toUpper(std::string in) {
    std::string result;
    for (char c : in) {
        result += toupper(c);
    }

    return result;
}

void wordleGame(std::ostream& os, std::istream& is, std::vector<std::string> words, std::vector<std::string> allowed,  Stat* wStats) {
    std::string chosenWordle = genWordle(words, RANDOM_NUM_BUCKETS);
    os << "Enter your guess:" << std::endl;
    bool win = false;
    int attempts = 0;
    while (attempts < 6 && !win) {
        std::string guess;
        std::getline(is, guess);
        bool isValid = checkValidGuess(allowed, guess);
        if (!isValid) {
            os << "You entered an invalid guess" << std::endl;
            os << "Guess " << guess << " not a valid guess or length != 5" << std::endl;
        } else {
            std::vector<int> colors = highlightGuess(guess, chosenWordle);
            displayGuess(os, guess, colors);
            writeOutput(guess, colors);
            if (checkWin(chosenWordle, guess)) {
                win = true;
            }

            attempts++;
        }
    }

    if (win) {
        os << std::endl << "Splendid!";
    } else {
        os << "The word was: " << toUpper(chosenWordle) << std::endl;
        os << std::endl << std::endl << "Better luck next time!" << std::endl << std::endl;
    }

    enterKeyEvent(is, os);
}
#endif