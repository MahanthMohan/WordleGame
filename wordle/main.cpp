#include <iostream>
#include "display.h"
#include "statistics.h"
#include "wordle.h"
using namespace std;

Stat* stats;
std::vector<std::string> allowed;
std::vector<std::string> words;

void wordleMenu(std::ostream& os, std::istream& is) {
    int opt = optionMenu(os, is);

    while (opt != 5) {
        if (opt == 1) {
            wordleGame(os, is, words, allowed, stats);
        } else if (opt == 2) {
            instrMenu(os, is);
        } else if (opt == 3) {

        } else if (opt == 4) {
            
        }

        std::string choice;
        std::getline(std::cin, choice);
        if (choice.length() > 0) {
            opt = std::stoi(choice);
        }
    }
}

int main(int argc, char* argv[]) {
    loadWords(words, allowed);
    stats = new Stat;
    stats->read();
    wordleMenu(std::cout, std::cin);
    return 0;
}