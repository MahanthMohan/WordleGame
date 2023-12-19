# Wordle Game
![logo](wordle.png)
A C++ implementation of the popular Wordle game created by the New York Times. It allows the user to make upto 6 guesses for a randomly generated 5 letter word.
## Key Features
 -  Highlighting characters depending on their position in the word and checking for a win.
 -  Keyboard window, constantly updating based on the contents of interface.txt, that records color of each character.
 -  View statistics (avg attempts, win percent, current streak, longest streak), and each random guess (win or lose)
## Packages/Libraries Used
 - C++ `stdlib`
## Build and Run Instructions
### Linux/Mac (with make installed)
Open 2 terminal windows - W1 for wordle and W2 for keyboard
 - On W1
``` bash
cd wordle && make
./app
```
``` Powershell
cd wordle && g++ -Wall -i . main.cpp -o app
.\app
```
 - On W2
 ``` bash
cd keyboard && make
./app
```
``` Powershell
cd keyboard && g++ -Wall -i . main.cpp -o app
./app
```
