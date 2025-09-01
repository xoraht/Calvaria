#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(const string& name, int level, int maxHP, int attack, int armor)
    : Character(name, level, maxHP, attack, armor), exp(0), gold(0),
      baseAttack(attack), baseArmor(armor),
      weapon(nullptr), helmet(nullptr), armorItem(nullptr), pants(nullptr), boots(nullptr) {
    updateExpToNextLevel();
}

void Player::addExperience(int amount) {
    exp += amount;
    while (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    maxHP += 30;
    hp = maxHP;
    baseAttack += 4;
    baseArmor += 2; 
    updateExpToNextLevel();

    attack = baseAttack;
    armor = baseArmor;
    if (weapon && weapon->equipped) attack += weapon->attackBonus;
    if (helmet && helmet->equipped) armor += helmet->armorBonus;
    if (armorItem && armorItem->equipped) armor += armorItem->armorBonus;
    if (pants && pants->equipped) armor += pants->armorBonus;
    if (boots && boots->equipped) armor += boots->armorBonus;

    cout << "\n*** Level Up! You are now level " << level << " ***\n";
    cout << "New stats: HP: " << hp << "/" << maxHP
         << ", Attack: " << attack << ", Armor: " << armor << endl;
}

void Player::updateExpToNextLevel() {
    expToNextLevel = 10 + (level - 1) * 8 + (level - 1) * (level - 1) * 3;
}

void Player::addGold(int amount) {
    gold += amount;
}

void Player::equip(Item* item) {
    for (auto& it : backpack) {
        if (it.type == item->type && it.equipped) {
            it.equipped = false;
        }
    }
    item->equipped = true;

    switch (item->type) {
        case ItemType::Weapon: weapon = item; break;
        case ItemType::Helmet: helmet = item; break;
        case ItemType::Armor: armorItem = item; break;
        case ItemType::Pants: pants = item; break;
        case ItemType::Boots: boots = item; break;
    }

    attack = baseAttack;
    armor = baseArmor;

    if (weapon && weapon->equipped) attack += weapon->attackBonus;
    if (helmet && helmet->equipped) armor += helmet->armorBonus;
    if (armorItem && armorItem->equipped) armor += armorItem->armorBonus;
    if (pants && pants->equipped) armor += pants->armorBonus;
    if (boots && boots->equipped) armor += boots->armorBonus;
}

void Player::addToBackpack(const Item& item) {
    backpack.push_back(item);
}

void Player::removeEquipment(ItemType type) {
    Item* slot = nullptr;
    switch (type) {
        case ItemType::Weapon: slot = weapon; break;
        case ItemType::Helmet: slot = helmet; break;
        case ItemType::Armor: slot = armorItem; break;
        case ItemType::Pants: slot = pants; break;
        case ItemType::Boots: slot = boots; break;
    }
    if (slot && slot->equipped) {
        slot->equipped = false;
        attack = baseAttack;
        armor = baseArmor;
        if (weapon && weapon->equipped) attack += weapon->attackBonus;
        if (helmet && helmet->equipped) armor += helmet->armorBonus;
        if (armorItem && armorItem->equipped) armor += armorItem->armorBonus;
        if (pants && pants->equipped) armor += pants->armorBonus;
        if (boots && boots->equipped) armor += boots->armorBonus;
    }
}

void Player::unlockSkill(int idx) {
    if (idx >= 0 && idx < skills.size()) {
        skills[idx].unlocked = true;
    }
}
void Player::resetSkillsForBattle() {
    for (auto& skill : skills) {
        skill.usedInBattle = false;
    }
}