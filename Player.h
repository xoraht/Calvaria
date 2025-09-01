#pragma once
#include "Character.h"
#include "Item.h"
#include <vector>
using namespace std;

enum class SkillType { None, WarriorAttack, WarriorHeal, WarriorUltimate, ArcherAttack, ArcherHeal, ArcherUltimate, MageAttack, MageHeal, MageUltimate };
struct Skill {
    string name;
    string description;
    int requiredLevel;
    bool unlocked;
    bool usedInBattle;
    SkillType type;
};

enum class Profession { None, Warrior, Archer, Mage };
class Player : public Character {
public:
    int exp;
    int expToNextLevel;
    int gold;

    int baseAttack;
    int baseArmor;
    int bossDefeatedLevel = 0;

    Item* weapon;
    Item* helmet;
    Item* armorItem;
    Item* pants;
    Item* boots;

    vector<Item> backpack;

    Profession profession = Profession::None;

    Player(const string& name, int level, int maxHP, int attack, int armor);
    void addExperience(int amount);
    void levelUp();
    void updateExpToNextLevel();
    void addGold(int amount);
    void equip(Item* item);
    void addToBackpack(const Item& item);
    void removeEquipment(ItemType type);
    vector<Skill> skills;
    void unlockSkill(int idx);
    void resetSkillsForBattle();
};