#include <iostream>
#include "keyboard.h"
using namespace std;

int main() {
    bool changed = true;
    while (changed) {
        system("cls");
        display(std::cout);
        _sleep(5000);
    }
    
    return 0;
}