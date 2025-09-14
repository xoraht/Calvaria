#pragma once
#include <iostream>
#include <string>
using namespace std;

class Character {
public:
    string name;
    int level;
    int hp;
    int maxHP;
    int attack;
    int armor;

    Character(const string& name, int level, int maxHP, int attack, int armor);
};