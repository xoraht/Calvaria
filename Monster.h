#pragma once
#include "Character.h"
#include <string>
#include <vector>
using namespace std;

class Monster : public Character {
public:
    int experience;
    Monster();
    Monster(const string& name, int level, int maxHP, int attack, int armor, int experience);

    static vector<Monster> getMonstersForLevel(int playerLevel);
    static Monster getRandomMonster(int playerLevel);

    static Monster getBossForLevel(int level);
};