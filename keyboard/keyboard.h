#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#ifndef KEYBOARD_H
#define KEYBOARD_H
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

static char KBD_CHARS[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
                    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
                    'Z', 'X', 'C', 'B', 'N', 'M', 'V'};

static int KEYBOARD_LEN[] = {10, 9, 7};

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
        os << color_code << "|" << std::setw(1) << "" << std::left << std::setw(2) << guess[i] << "|" << RESET_CODE;
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

std::vector<std::vector<std::string>> readWordleOutput() {
    std::ifstream ifs;
    std::vector<std::vector<std::string>> wleOutput;
    ifs.open("../wordle/interface.txt");

    if (!ifs.is_open()) {
        return wleOutput;
    }

    std::string line;
    while (std::getline(ifs, line, '\n')) {
        std::istringstream lss(line);
        std::string temp;
        std::vector<std::string> hltChar;
        while (std::getline(lss, temp, ',')) {
            hltChar.push_back(temp);
        }

        wleOutput.push_back(hltChar);
    }

    ifs.close();
    return wleOutput;
}

void display(std::ostream& os) {
    std::vector<std::vector<std::string>> wordleOutput = readWordleOutput();
    int char_counter = 0;
    for (int j = 0; j < 3; j++) {
        std::string kline;
        std::vector<int> line_colors;
        int kl = KEYBOARD_LEN[j];
        for (int i = 0; i < kl; i++) {
            char c = KBD_CHARS[char_counter + i];
            int index = -1;
            int color = WHITE;

            for (int i = 0; i < wordleOutput.size() && index == -1; i++) {
                std::vector<std::string> hltOutput = wordleOutput[i];
                char cur = hltOutput[0][0];
                if (tolower(c) == cur) {
                    index = i;
                    color = std::stoi(hltOutput[1]);
                }
            }

            kline += c;
            line_colors.push_back(color);
        }

        char_counter += kl;
        displayGuess(os, kline, line_colors);
    }
}

#endif