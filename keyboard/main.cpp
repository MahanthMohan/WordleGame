#include <iostream>
#include "keyboard.h"
using namespace std;

int main() {
    bool changed = true;
    while (changed) {
        system("cls");
        display(std::cout);
        _sleep(4000);
    }
    
    return 0;
}