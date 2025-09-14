#pragma once
#include <string>
using namespace std;
enum class SkillType {
    None,
    WarriorAttack, WarriorHeal, WarriorUltimate,
    ArcherAttack, ArcherHeal, ArcherUltimate,
    MageAttack, MageHeal, MageUltimate
};

struct Skill {
    string name;
    string description;
    int requiredLevel;
    bool unlocked;
    bool usedInBattle;
    SkillType type;
};