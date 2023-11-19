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
            enterKeyEvent(is, os);
        } else if (opt == 2) {
            instrMenu(os, is);
            enterKeyEvent(is, os);
        } else if (opt == 3) {
            stats->display(os, 27);
            cout << endl << endl;
            enterKeyEvent(is, os);
        } else if (opt == 4) {
            stats->reset();
            cout << endl << endl;
            enterKeyEvent(is, os); 
        }

        opt = optionMenu(os, is);
    }

    std::cout << "See you soon!" << endl;
}

void clearGuess() {
    std::ofstream ofs;
    ofs.open("interface.txt", std::fstream::trunc);
    ofs.close();
}

int main(int argc, char* argv[]) {
    clearGuess();
    loadWords(words, allowed);
    stats = new Stat();
    stats->read();
    wordleMenu(std::cout, std::cin);
    return 0;
}