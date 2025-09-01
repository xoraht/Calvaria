#include "Character.h"

Character::Character(const string& name, int level, int maxHP, int attack, int armor)
    : name(name), level(level), hp(maxHP), maxHP(maxHP), attack(attack), armor(armor) {}