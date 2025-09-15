#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include "Menu.h"
#include "Game.h"
using namespace std;

void launch() {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, 14);
    cout << endl << setw(50) << "~~~~~~~~~~~~~~~~ Calvaria Game ~~~~~~~~~~~~~~~~" << endl << endl;
    SetConsoleTextAttribute(color, 2);
    cout << setw(35) << "[ENTER] START GAME" << endl;
    SetConsoleTextAttribute(color, 7);
    cout << setw(35) << "[ESCAPE] EXIT GAME" << endl << endl;
    SetConsoleTextAttribute(color, 14);
    cout << setw(50) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

    if (_getch() == 13) {
        system("cls");
        begin();
    } else if (_getch() == 27) {
        exit(0);
    }
}