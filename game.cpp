#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include "Game.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
using namespace std;

map<int, vector<Item>> shopInventory;
HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);

string getAttackName(Profession prof) {
    switch (prof) {
        case Profession::Warrior: return "Sword Slash";
        case Profession::Archer: return "Arrow Shot";
        case Profession::Mage: return "Magic Ball";
        default: return "Attack";
    }
}

vector<Skill> getSkillsForProfession(Profession prof) {
    vector<Skill> skills;
    if (prof == Profession::Warrior) {
        skills.push_back({ "Power Strike", "Deal heavy damage (lvl 10)", 10, false, false, SkillType::WarriorAttack });
        skills.push_back({ "Battle Heal", "Heal yourself (lvl 30)", 30, false, false, SkillType::WarriorHeal });
        skills.push_back({ "Unbreakable", "Reduce all damage for 1 turn (lvl 50)", 50, false, false, SkillType::WarriorUltimate });
        skills.push_back({ "Berserk", "Double attack for 1 turn (lvl 70)", 70, false, false, SkillType::None });
        skills.push_back({ "Last Stand", "Heal to 50% HP (lvl 90)", 90, false, false, SkillType::None });
        skills.push_back({ "Final Blow", "Massive damage (lvl 100)", 100, false, false, SkillType::None });
    }
    else if (prof == Profession::Archer) {
        skills.push_back({ "Piercing Arrow", "Ignore armor (lvl 10)", 10, false, false, SkillType::ArcherAttack });
        skills.push_back({ "Quick Step", "Evade next attack (lvl 30)", 30, false, false, SkillType::None });
        skills.push_back({ "Volley", "Attack multiple times (lvl 50)", 50, false, false, SkillType::ArcherUltimate });
        skills.push_back({ "Focus", "Increase crit chance (lvl 70)", 70, false, false, SkillType::None });
        skills.push_back({ "Second Wind", "Heal 30% HP (lvl 90)", 90, false, false, SkillType::ArcherHeal });
        skills.push_back({ "Rain of Arrows", "Heavy damage to all (lvl 100)", 100, false, false, SkillType::None });
    }
    else if (prof == Profession::Mage) {
        skills.push_back({ "Fireball", "Magic damage (lvl 10)", 10, false, false, SkillType::MageAttack });
        skills.push_back({ "Mana Shield", "Block next attack (lvl 30)", 30, false, false, SkillType::None });
        skills.push_back({ "Heal", "Restore HP (lvl 50)", 50, false, false, SkillType::MageHeal });
        skills.push_back({ "Lightning", "Stun enemy (lvl 70)", 70, false, false, SkillType::None });
        skills.push_back({ "Arcane Surge", "Boost all stats (lvl 90)", 90, false, false, SkillType::None });
        skills.push_back({ "Meteor", "Massive magic damage (lvl 100)", 100, false, false, SkillType::MageUltimate });
    }
    return skills;
}

vector<Item> getShopItemsForLevel(int level) {
    vector<Item> items;
    if (level < 10) {
        items.push_back(Item("Wooden Sword", ItemType::Weapon, 10, 3, 0));
        items.push_back(Item("Leather Helmet", ItemType::Helmet, 8, 0, 2));
        items.push_back(Item("Leather Armor", ItemType::Armor, 12, 0, 4));
        items.push_back(Item("Leather Legs", ItemType::Pants, 7, 0, 2));
        items.push_back(Item("Leather Boots", ItemType::Boots, 5, 0, 2));
    } else if (level < 20) {
        items.push_back(Item("Silver Sword", ItemType::Weapon, 25, 6, 0));
        items.push_back(Item("Chain Helmet", ItemType::Helmet, 20, 0, 4));
        items.push_back(Item("Chain Armor", ItemType::Armor, 30, 0, 8));
        items.push_back(Item("Chain Legs", ItemType::Pants, 15, 0, 4));
        items.push_back(Item("Chain Boots", ItemType::Boots, 12, 0, 3));
    } else if (level < 30) {
        items.push_back(Item("Short Sword", ItemType::Weapon, 50, 10, 0));
        items.push_back(Item("Brass Helmet", ItemType::Helmet, 40, 0, 6));
        items.push_back(Item("Brass Armor", ItemType::Armor, 60, 0, 12));
        items.push_back(Item("Brass Legs", ItemType::Pants, 30, 0, 6));
        items.push_back(Item("Brass Boots", ItemType::Boots, 25, 0, 5));
    } else if (level < 40) {
        items.push_back(Item("Spike Sword", ItemType::Weapon, 90, 16, 0));
        items.push_back(Item("Legion Helmet", ItemType::Helmet, 70, 0, 9));
        items.push_back(Item("Legion Armor", ItemType::Armor, 120, 0, 18));
        items.push_back(Item("Legion Legs", ItemType::Pants, 55, 0, 8));
        items.push_back(Item("Legion Boots", ItemType::Boots, 40, 0, 7));
    } else if (level < 50) {
        items.push_back(Item("Fire Sword", ItemType::Weapon, 150, 22, 0));
        items.push_back(Item("Scale Helmet", ItemType::Helmet, 120, 0, 12));
        items.push_back(Item("Scale Armor", ItemType::Armor, 200, 0, 24));
        items.push_back(Item("Scale Legs", ItemType::Pants, 90, 0, 10));
        items.push_back(Item("Scale Boots", ItemType::Boots, 65, 0, 8));
    } else if (level < 60) {
        items.push_back(Item("Bright Sword", ItemType::Weapon, 220, 28, 0));
        items.push_back(Item("Soldier Helmet", ItemType::Helmet, 180, 0, 15));
        items.push_back(Item("Soldier Armor", ItemType::Armor, 300, 0, 32));
        items.push_back(Item("Soldier Legs", ItemType::Pants, 130, 0, 12));
        items.push_back(Item("Soldier Boots", ItemType::Boots, 90, 0, 10));
    } else if (level < 70) {
        items.push_back(Item("Relic Sword", ItemType::Weapon, 300, 35, 0));
        items.push_back(Item("Plate Helmet", ItemType::Helmet, 250, 0, 18));
        items.push_back(Item("Plate Armor", ItemType::Armor, 400, 0, 40));
        items.push_back(Item("Plate Legs", ItemType::Pants, 170, 0, 15));
        items.push_back(Item("Plate Boots", ItemType::Boots, 120, 0, 12));
    } else if (level < 80) {
        items.push_back(Item("Dragon Sword", ItemType::Weapon, 400, 42, 0));
        items.push_back(Item("Royal Helmet", ItemType::Helmet, 320, 0, 22));
        items.push_back(Item("Royal Armor", ItemType::Armor, 550, 0, 48));
        items.push_back(Item("Royal Legs", ItemType::Pants, 220, 0, 18));
        items.push_back(Item("Royal Boots", ItemType::Boots, 160, 0, 14));
    } else if (level < 90) {
        items.push_back(Item("Giant Sword", ItemType::Weapon, 550, 50, 0));
        items.push_back(Item("Crusader Helmet", ItemType::Helmet, 420, 0, 26));
        items.push_back(Item("Crusader Armor", ItemType::Armor, 700, 0, 56));
        items.push_back(Item("Crusader Legs", ItemType::Pants, 300, 0, 20));
        items.push_back(Item("Crusader Boots", ItemType::Boots, 210, 0, 16));
    } else if (level < 100) {
        items.push_back(Item("Warlord Sword", ItemType::Weapon, 700, 60, 0));
        items.push_back(Item("Demon Helmet", ItemType::Helmet, 550, 0, 30));
        items.push_back(Item("Demon Armor", ItemType::Armor, 900, 0, 64));
        items.push_back(Item("Demon Legs", ItemType::Pants, 380, 0, 24));
        items.push_back(Item("Demon Boots", ItemType::Boots, 270, 0, 18));
    } else {
        items.push_back(Item("Magic sword", ItemType::Weapon, 1000, 80, 0));
        items.push_back(Item("Golden Helmet", ItemType::Helmet, 800, 0, 40));
        items.push_back(Item("Magic Plate Armor", ItemType::Armor, 1500, 0, 90));
        items.push_back(Item("Dragon Scale Legs", ItemType::Pants, 600, 0, 35));
        items.push_back(Item("Golden Boots", ItemType::Boots, 400, 0, 25));
    }
    return items;
}


void showCharacterInfo(Player& player) {
    system("cls");
    SetConsoleTextAttribute(color, 14);
    cout << endl << setw(50) << "~~~~~~~~~~~~ Character Information ~~~~~~~~~~~~" << endl << endl;
    SetConsoleTextAttribute(color, 15);
    cout << setw(9) << "Name: " << player.name << endl;
    SetConsoleTextAttribute(color, 7);
    cout << setw(10) << "Level: " << player.level << " | " << player.exp << " / " << player.expToNextLevel << endl;
    SetConsoleTextAttribute(color, 10);
    cout << setw(11) << "Health: " << player.hp << "/" << player.maxHP << endl;
    SetConsoleTextAttribute(color, 12);
    cout << setw(11) << "Attack: " << player.attack << endl;
	SetConsoleTextAttribute(color, 11);
    cout << setw(10) << "Armor: " << player.armor << endl;
    SetConsoleTextAttribute(color, 6);
    cout << setw(9) << "Gold: " << player.gold << endl;

    SetConsoleTextAttribute(color, 14);
    cout << endl << setw(50) << "~~~~~~~~~~~~~~~ Your Equipment ~~~~~~~~~~~~~~~~" << endl << endl;
    SetConsoleTextAttribute(color, 15);
    cout << setw(15) << "[1] Weapon: " << (player.weapon && player.weapon->equipped ? player.weapon->name : "None") << endl;
    cout << setw(15) << "[2] Helmet: " << (player.helmet && player.helmet->equipped ? player.helmet->name : "None") << endl;
    cout << setw(14) << "[3] Armor: " << (player.armorItem && player.armorItem->equipped ? player.armorItem->name : "None") << endl;
    cout << setw(14) << "[4] Pants: " << (player.pants && player.pants->equipped ? player.pants->name : "None") << endl;
    cout << setw(14) << "[5] Boots: " << (player.boots && player.boots->equipped ? player.boots->name : "None") << endl;
    SetConsoleTextAttribute(color, 7);
    cout << endl << setw(23) << "Press [ESC] to back." << endl;
    char key = _getch();
    if (key == 27) {
        system("cls");
        return;
    }
    int idx = key - '1';
    if (idx >= 0 && idx < 5) {
        ItemType type = static_cast<ItemType>(idx);
        player.removeEquipment(type);
        SetConsoleTextAttribute(color, 10);
        cout << endl << setw(19) << "Item unequipped!" << endl;
        (void)_getch();
    }
    system("cls");
}

void showBackpack(Player& player) {
    system("cls");
    SetConsoleTextAttribute(color, 14);
    cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~ Backpack ~~~~~~~~~~~~~~~~~~~" << endl << endl;
    int count = 0;
    SetConsoleTextAttribute(color, 15);
    for (size_t i = 0; i < player.backpack.size(); i++) {
        if (!player.backpack[i].equipped) {
            cout << setw(4) << "[" << count + 1 << "] " << player.backpack[i].name << endl;
            count++;
        }
    }
    if (count == 0) cout  << setw(13) << "Nothing..." << endl;
    SetConsoleTextAttribute(color, 7);
    cout << endl << setw(23) << "Press [ESC] to back." << endl;
    char key = _getch();
    if (key == 27 || count == 0) {
        system("cls");
        return;
    }
    int idx = key - '1';
    size_t realIdx = static_cast<size_t>(-1);
    count = 0;
    for (size_t i = 0; i < player.backpack.size(); i++) {
        if (!player.backpack[i].equipped) {
            if (count == idx) {
                realIdx = i;
                break;
            }
            count++;
        }
    }
    if (realIdx != static_cast<size_t>(-1)) {
        player.equip(&player.backpack[realIdx]);
        SetConsoleTextAttribute(color, 10);
        cout << endl << setw(12) << "Equipped " << player.backpack[realIdx].name << "!" << endl;
        (void)_getch();
    }
    system("cls");
}

void fight(Player& player) {
    player.resetSkillsForBattle();
    bool isBossLevel = (player.level % 5 == 0);
    bool bossAlreadyAttempted = isBossLevel && (player.bossDefeatedLevel == player.level);

    Monster monster;
    if (isBossLevel && !bossAlreadyAttempted) {
        monster = Monster::getBossForLevel(player.level);
    } else {
        monster = Monster::getRandomMonster(player.level);
    }

    string battleLog = "The fight has begun! You face " + monster.name + ".";
    bool escaped = false;

    while (player.hp > 0 && monster.hp > 0 && !escaped) {
        system("cls");
        SetConsoleTextAttribute(color, 14);
        cout << endl << setw(18) << "~~~~~~~~~~~~~~ " << player.name << " VS " << monster.name << " ~~~~~~~~~~~~~~" << endl << endl;
        SetConsoleTextAttribute(color, 15);
        cout << setw(19) << "Your Statistics:" << endl;
        SetConsoleTextAttribute(color, 10);
        cout << setw(11) << "Health: " << player.hp << "/" << player.maxHP << "   Attack: " << player.attack << "   Armor: " << player.armor << endl;
        SetConsoleTextAttribute(color, 15);
        cout << setw(21) << "Enemy Statistics: " << endl;
        SetConsoleTextAttribute(color, 12);
        cout << setw(11) << "Health: " << monster.hp << "/" << monster.maxHP << "   Attack: " << monster.attack << "   Armor: " << monster.armor << endl;
        SetConsoleTextAttribute(color, 14);
        cout << setw(47) << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        SetConsoleTextAttribute(color, 15);
        cout << setw(42) << battleLog << endl;
        SetConsoleTextAttribute(color, 14);
        cout << setw(47) << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        SetConsoleTextAttribute(color, 13);
        cout << setw(7) << "[A] " << getAttackName(player.profession) << "   [E] Escape" << endl;

        int skillKeyOffset = 1;
        for (size_t i = 0; i < player.skills.size(); i++) {
            const Skill& skill = player.skills[i];
            if (skill.unlocked && !skill.usedInBattle) {
                cout << setw(4) << "[" << (char)('1' + i) << "] Use skill: " << skill.name << endl;
            }
        }

        char action = _getch();
        battleLog = "";

        if (action == 'a' || action == 'A') {
            int damage = max(1, player.attack - monster.armor);
            monster.hp -= damage;
            battleLog += "You use " + getAttackName(player.profession) + " on " + monster.name + " for " + to_string(damage) + " damage.\n";
            if (monster.hp > 0) {
                int enemyDamage = max(1, monster.attack - player.armor);
                player.hp -= enemyDamage;
                battleLog += monster.name + " attacks you for " + to_string(enemyDamage) + " damage.";
            } else {
                battleLog += "You have defeated " + monster.name + "!";
            }
        } else if (action == 'e' || action == 'E') {
            int chance = rand() % 100;
            if (chance < 30) {
                battleLog += "You successfully escaped!";
                escaped = true;
            } else {
                battleLog += "Escape failed! You lose your turn.\n";
                int enemyDamage = max(1, monster.attack - player.armor);
                player.hp -= enemyDamage;
                battleLog += monster.name + " attacks you for " + to_string(enemyDamage) + " damage.";
            }
        } else if (action >= '1' && action < '1' + player.skills.size()) {
            int idx = action - '1';
            Skill& skill = player.skills[idx];
            if (skill.unlocked && !skill.usedInBattle) {
                skill.usedInBattle = true;
                switch (skill.type) {
                    case SkillType::WarriorAttack:
                        battleLog += "You use Power Strike! Massive damage!\n";
                        monster.hp -= player.attack * 2;
                        break;
                    case SkillType::WarriorHeal:
                        battleLog += "You use Battle Heal! You recover 40 HP.\n";
                        player.hp = min(player.maxHP, player.hp + 40);
                        break;
                    case SkillType::WarriorUltimate:
                        battleLog += "You use Unbreakable! Enemy deals half damage next turn.\n";
                        monster.attack = monster.attack / 2;
                        break;
                    case SkillType::ArcherAttack:
                        battleLog += "You use Piercing Arrow! Ignores armor.\n";
                        monster.hp -= max(1, player.attack);
                        break;
                    case SkillType::ArcherHeal:
                        battleLog += "You use Second Wind! You recover 30% HP.\n";
                        player.hp = min(player.maxHP, player.hp + player.maxHP * 3 / 10);
                        break;
                    case SkillType::ArcherUltimate:
                        battleLog += "You use Volley! Multiple attacks!\n";
                        monster.hp -= max(1, player.attack - monster.armor) * 3;
                        break;
                    case SkillType::MageAttack:
                        battleLog += "You use Fireball! Magic damage!\n";
                        monster.hp -= player.attack + 20;
                        break;
                    case SkillType::MageHeal:
                        battleLog += "You use Heal! You recover 50 HP.\n";
                        player.hp = min(player.maxHP, player.hp + 50);
                        break;
                    case SkillType::MageUltimate:
                        battleLog += "You use Meteor! Massive magic damage!\n";
                        monster.hp -= player.attack * 3;
                        break;
                    default:
                        battleLog += "You use " + skill.name + "! Effect applied.\n";
                        break;
                }
                if (monster.hp > 0) {
                    int enemyDamage = max(1, monster.attack - player.armor);
                    player.hp -= enemyDamage;
                    battleLog += monster.name + " attacks you for " + to_string(enemyDamage) + " damage.";
                } else {
                    battleLog += "You have defeated " + monster.name + "!";
                }
            } else {
                battleLog += "Skill not available.";
            }
        } else {
            battleLog = "Invalid action!";
        }
    }

    system("cls");
    SetConsoleTextAttribute(color, 14);
	cout << endl << setw(50) << "~~~~~~~~~~~~~~~~ Battle Result ~~~~~~~~~~~~~~~~" << endl << endl;
    if (escaped) {
        SetConsoleTextAttribute(color, 15);
        cout << setw(30) << "You escaped from the fight!" << endl;
    } else if (player.hp <= 0) {
		SetConsoleTextAttribute(color, 12);
        cout << setw(28) << "You were defeated by the " << monster.name << "..." << endl;
    } else if (monster.hp <= 0) {
        SetConsoleTextAttribute(color, 10);
        cout << setw(20) << "You defeated the " << monster.name << "!" << endl;
        player.addExperience(monster.experience);
        SetConsoleTextAttribute(color, 11);
        cout << setw(14) << "You gained " << monster.experience << " experience!" << endl;
        SetConsoleTextAttribute(color, 6);
        player.addGold(monster.level);
        cout << setw(14) << "You gained " << monster.level << " gold!" << endl;
    }
    if (isBossLevel && !bossAlreadyAttempted) {
        player.bossDefeatedLevel = player.level;
    }
    player.hp = player.maxHP;
    SetConsoleTextAttribute(color, 7);
    cout << endl << setw(23) << "Press [ESC] to back." << endl;
    while (_getch() != 27) {}
    system("cls");
}

void shop(Player& player) {
    int shopTier = (player.level / 10) * 10;
    if (shopTier > 100) shopTier = 100;
    if (shopInventory.find(shopTier) == shopInventory.end()) {
        shopInventory[shopTier] = getShopItemsForLevel(player.level);
    }
    vector<Item>& items = shopInventory[shopTier];

    while (true) {
        system("cls");
        SetConsoleTextAttribute(color, 14);
        cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~~~ SHOP ~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        SetConsoleTextAttribute(color, 10);
        cout << setw(17) << "[B] Buy items" << endl;
        SetConsoleTextAttribute(color, 12);
        cout << setw(18) << "[S] Sell items" << endl << endl;
        SetConsoleTextAttribute(color, 7);
        cout << setw(19) << "[ESC] Exit shop" << endl;
        char key = _getch();
        if (key == 27) break;

        if (key == 'b' || key == 'B') {
            while (true) {
                system("cls");
                SetConsoleTextAttribute(color, 14);
                cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~ SHOP - BUY ~~~~~~~~~~~~~~~~~" << endl << endl;
                SetConsoleTextAttribute(color, 6);
                cout << setw(15) << "Your gold: " << player.gold << endl << endl;
                if (items.empty()) {
                    SetConsoleTextAttribute(color, 15);
                    cout << setw(30) << "No items available to buy." << endl << endl;
                    SetConsoleTextAttribute(color, 7);
                    cout << setw(19) << "[ESC] Exit shop" << endl;
                    if (_getch() == 27) break;
                    continue;
                }
                for (size_t i = 0; i < items.size(); ++i) {
                    SetConsoleTextAttribute(color, 15);
                    cout << setw(5) << "[" << i + 1 << "] " << items[i].name << " (Price: " << items[i].price << ")" << endl;
                }
                SetConsoleTextAttribute(color, 7);
                cout << endl << setw(19) << "[ESC] Exit shop" << endl;
                char buyKey = _getch();
                if (buyKey == 27) break;
                int idx = buyKey - '1';
                if (idx >= 0 && idx < items.size()) {
                    if (player.gold >= items[idx].price) {
                        player.gold -= items[idx].price;
                        player.addToBackpack(items[idx]);
                        SetConsoleTextAttribute(color, 15);
                        cout << endl << setw(15) << "You bought " << items[idx].name << "!" << endl;
                        items.erase(items.begin() + idx);
                    } else {
                        SetConsoleTextAttribute(color, 12);
                        cout << endl << setw(20) << "Not enough gold!" << endl;
                    }
                    SetConsoleTextAttribute(color, 15);
                    cout << setw(20) << "Press any key..." << endl;
                    (void)_getch();
                }
            }
        } else if (key == 's' || key == 'S') {
            while (true) {
                system("cls");
                SetConsoleTextAttribute(color, 14);
                cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~ SHOP - SELL ~~~~~~~~~~~~~~~~" << endl << endl;
                SetConsoleTextAttribute(color, 6);
                cout << setw(15) << "Your gold: " << player.gold << endl << endl;

                vector<size_t> sellableIndices;
                for (size_t i = 0; i < player.backpack.size(); i++) {
                    if (!player.backpack[i].equipped) {
                        sellableIndices.push_back(i);
                    }
                }

                if (sellableIndices.empty()) {
                    SetConsoleTextAttribute(color, 15);
                    cout << setw(49) << "No unequipped items to sell in your backpack." << endl << endl;
                    SetConsoleTextAttribute(color, 7);
                    cout << setw(19) << "[ESC] Exit shop" << endl;
                    if (_getch() == 27) break;
                    continue;
                }

                for (size_t i = 0; i < sellableIndices.size(); ++i) {
                    size_t idx = sellableIndices[i];
                    SetConsoleTextAttribute(color, 15);
                    cout << setw(5) << "[" << i + 1 << "] " << player.backpack[idx].name
                         << " (Sell price: " << player.backpack[idx].price / 2 << ")" << endl;
                }
                SetConsoleTextAttribute(color, 7);
                cout << endl << setw(19) << "[ESC] Exit shop" << endl << endl;
                char sellKey = _getch();
                if (sellKey == 27) break;
                int choice = sellKey - '1';
                if (choice >= 0 && choice < sellableIndices.size()) {
                    size_t realIdx = sellableIndices[choice];
                    int sellPrice = player.backpack[realIdx].price / 2;
                    player.gold += sellPrice;
                    SetConsoleTextAttribute(color, 10);
                    cout << setw(13) << "You sold " << player.backpack[realIdx].name << " for " << sellPrice << " gold!" << endl;
                    player.backpack.erase(player.backpack.begin() + realIdx);
                    SetConsoleTextAttribute(color, 15);
                    cout << setw(20) << "Press any key..." << endl;
                    (void)_getch();
                }
            }
        }
    }
    system("cls");
}

void temple(Player& player) {
    system("cls");
    if (player.level < 10) {
        SetConsoleTextAttribute(color, 14);
        cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~~~ TEMPLE ~~~~~~~~~~~~~~~~~~~" << endl << endl;
        cout << setw(36) << "You need to be at least level 10." << endl;
        SetConsoleTextAttribute(color, 7);
        cout << endl << setw(23) << "Press [ESC] to back." << endl;
        char key = _getch();
        if (key == 27) {
            system("cls");
            return;
        }
    }
    if (player.profession == Profession::None) {
        SetConsoleTextAttribute(color, 14);
        cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~~~ TEMPLE ~~~~~~~~~~~~~~~~~~~" << endl << endl;
        SetConsoleTextAttribute(color, 15);
        cout << setw(26) << "Choose your profession:" << endl << endl;
        SetConsoleTextAttribute(color, 12);
        cout << setw(14) << "[1] Warrior" << endl;
        SetConsoleTextAttribute(color, 8);
        cout << setw(13) << "[2] Archer" << endl;
        SetConsoleTextAttribute(color, 13);
        cout << setw(11) << "[3] Mage" << endl;
        SetConsoleTextAttribute(color, 7);
        cout << endl << setw(23) << "Press [ESC] to back." << endl;
        char key = _getch();
        if (key == '1') player.profession = Profession::Warrior;
        else if (key == '2') player.profession = Profession::Archer;
        else if (key == '3') player.profession = Profession::Mage;
        else if (key == 27) {
            system("cls");
            return;
        }
        player.skills = getSkillsForProfession(player.profession);
        system("cls");
    }
    SetConsoleTextAttribute(color, 14);
    cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~~~ TEMPLE ~~~~~~~~~~~~~~~~~~~" << endl << endl;
    for (size_t i = 0; i < player.skills.size(); i++) {
        const Skill& skill = player.skills[i];
        SetConsoleTextAttribute(color, 15);
        cout << setw(4) << "[" << i + 1 << "] " << skill.name << " - " << skill.description
            << " (Required level: " << skill.requiredLevel << ") ";
        if (skill.unlocked) { SetConsoleTextAttribute(color, 10); cout << "[UNLOCKED]"; }
        else if (player.level >= skill.requiredLevel) { SetConsoleTextAttribute(color, 11); cout << "[AVAILABLE]"; }
        else { SetConsoleTextAttribute(color, 12); cout << "[LOCKED]"; }
        cout << endl;
    }
    SetConsoleTextAttribute(color, 7);
    cout << endl << setw(23) << "Press [ESC] to back." << endl;
    char key = _getch();
    if (key == 27) {
        system("cls");
        return;
    }
    int idx = key - '1';
    if (idx >= 0 && idx < player.skills.size()) {
        Skill& skill = player.skills[idx];
        if (!skill.unlocked && player.level >= skill.requiredLevel) {
            player.unlockSkill(idx);
            SetConsoleTextAttribute(color, 15);
            cout << endl << setw(19) << "Skill unlocked: " << skill.name << "!" << endl;
        }
        (void)_getch();
    }
    system("cls");
}

void gameMenu(Player& player) {
    while (true) {
        SetConsoleTextAttribute(color, 14);
        cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~ GAME MENU ~~~~~~~~~~~~~~~~~~" << endl << endl;
		SetConsoleTextAttribute(color, 15);
        cout << setw(28) << "[C] Character Information" << endl;
		SetConsoleTextAttribute(color, 8);
        cout << setw(15) << "[B] Backpack" << endl;
		SetConsoleTextAttribute(color, 12);
        cout << setw(12) << "[F] Fight" << endl;
		SetConsoleTextAttribute(color, 11);
        cout << setw(11) << "[S] Shop" << endl;
		SetConsoleTextAttribute(color, 13);
        cout << setw(13) << "[T] Temple" << endl;
		SetConsoleTextAttribute(color, 7);
        cout << setw(26) << "[ESC] Exit to main menu" << endl;
        char key = _getch();
        if (key == 'c' || key == 'C') {
            showCharacterInfo(player);
        } else if (key == 'b' || key == 'B') {
            showBackpack(player);
        } else if (key == 'f' || key == 'F') {
            fight(player);
        } else if (key == 's' || key == 'S') {
            shop(player);
        } else if (key == 't' || key == 'T') {
            temple(player);
        } else if (key == 27) {
            system("cls");
            break;
        }
        system("cls");
    }
}

void begin() {
    SetConsoleTextAttribute(color, 14);
    srand((unsigned)time(nullptr));
    string characterName;
    cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~ YOUR NAME ~~~~~~~~~~~~~~~~~~" << endl << endl << "   > ";
    SetConsoleTextAttribute(color, 15);
    cin >> characterName;
    system("cls");
    Player player(characterName, 9, 100, 30, 10);
    gameMenu(player);
}

