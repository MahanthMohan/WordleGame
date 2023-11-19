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
            enterKeyEvent(is, os);
        } else if (opt == 3) {
            std::string stat = stats->toString(27);
            cout << stat << endl;
            enterKeyEvent(is, os);
        } else if (opt == 4) {
            stats->reset();
            enterKeyEvent(is, os);   
        }

        opt = optionMenu(os, is);
    }
}

int main(int argc, char* argv[]) {
    loadWords(words, allowed);
    // for (auto& v : words) {
    //     std::cout << v << " ";
    // }
    // cout << endl;

    // for (auto& v : allowed) {
    //     std::cout << v << " ";
    // }
    // cout << endl;
    stats = new Stat;
    stats->read();
    wordleMenu(std::cout, std::cin);
    return 0;
}