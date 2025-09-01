#include <string>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <map>
#include <vector>
#include <iomanip>
#include "game.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
using namespace std;

map<int, vector<Item>> shopInventory;

void showCharacterInfo(Player& player) {
    system("cls");
    cout << "Character Information\n";
    cout << "---------------------\n";
    cout << "Name: " << player.name << endl;
    cout << "Level: " << player.level << endl;
    cout << "Experience: " << player.exp << " / " << player.expToNextLevel << endl;
    cout << "HP: " << player.hp << "/" << player.maxHP << endl;
    cout << "Gold: " << player.gold << endl;
    cout << "Attack: " << player.attack << endl;
    cout << "Armor: " << player.armor << endl;

    cout << "\nEquipped items:\n";
    cout << "[1] Weapon: " << (player.weapon && player.weapon->equipped ? player.weapon->name : "None") << endl;
    cout << "[2] Helmet: " << (player.helmet && player.helmet->equipped ? player.helmet->name : "None") << endl;
    cout << "[3] Armor: " << (player.armorItem && player.armorItem->equipped ? player.armorItem->name : "None") << endl;
    cout << "[4] Pants: " << (player.pants && player.pants->equipped ? player.pants->name : "None") << endl;
    cout << "[5] Boots: " << (player.boots && player.boots->equipped ? player.boots->name : "None") << endl;

    cout << "\nSelect item number to unequip or ESC to return...\n";
    char key = _getch();
    if (key == 27) {
        system("cls");
        return;
    }
    int idx = key - '1';
    if (idx >= 0 && idx < 5) {
        ItemType type = static_cast<ItemType>(idx);
        player.removeEquipment(type);
        cout << "Item unequipped!\n";
        cout << "Press any key...\n";
        (void)_getch();
    }
    system("cls");
}

void temple(Player& player);

void showBackpack(Player& player) {
    system("cls");
    cout << "Backpack\n";
    cout << "---------------------\n";
    int count = 0;
    for (size_t i = 0; i < player.backpack.size(); ++i) {
        if (!player.backpack[i].equipped) {
            cout << "[" << count + 1 << "] " << player.backpack[i].name << endl;
            count++;
        }
    }
    if (count == 0) cout << "No unequipped items in backpack.\n";
    cout << "\nSelect item number to equip or ESC to return...\n";
    char key = _getch();
    if (key == 27 || count == 0) {
        system("cls");
        return;
    }
    int idx = key - '1';
    size_t realIdx = static_cast<size_t>(-1);
    count = 0;
    for (size_t i = 0; i < player.backpack.size(); ++i) {
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
        cout << "Equipped " << player.backpack[realIdx].name << "!\n";
        (void)_getch();
    }
    system("cls");
}

void gameMenu(Player& player) {
    while (true) {
        cout << "~~~~~~~~~~~~~~~~~~ GAME MENU ~~~~~~~~~~~~~~~~~~" << endl;
        cout << "---------------------\n";
        cout << "[C] Character Information\n";
        cout << "[B] Backpack\n";
        cout << "[F] Fight\n";
        cout << "[S] Shop\n";
        cout << "[T] Temple\n";
        cout << "[ESC] Exit to main menu\n";
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
    srand((unsigned)time(nullptr));
    string characterName;
    cout << endl << setw(50) << "~~~~~~~~~~~~~~~~~~ YOUR NAME ~~~~~~~~~~~~~~~~~~" << endl << endl << "   > ";
    cin >> characterName;
    system("cls");
    Player player(characterName, 10, 100, 30, 10);
    gameMenu(player);
}

string getAttackName(Profession prof) {
    switch (prof) {
        case Profession::Warrior: return "Sword Slash";
        case Profession::Archer: return "Arrow Shot";
        case Profession::Mage: return "Magic Bolt";
        default: return "Attack";
    }
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

    string battleLog = "The fight has begun!\nYou face " + monster.name + ".";
    bool escaped = false;

    while (player.hp > 0 && monster.hp > 0 && !escaped) {
        system("cls");
        cout << "Your stats:\n";
        cout << "HP: " << player.hp << "/" << player.maxHP << "   Attack: " << player.attack << "   Armor: " << player.armor << endl;
        cout << "Enemy: " << monster.name << "\n";
        cout << "HP: " << monster.hp << "/" << monster.maxHP << "   Attack: " << monster.attack << "   Armor: " << monster.armor << endl;
        cout << "--------------------------------------------------\n";
        cout << battleLog << endl;
        cout << "--------------------------------------------------\n";
        cout << "[A] " << getAttackName(player.profession) << "   [E] Escape\n";

        int skillKeyOffset = 1;
        for (size_t i = 0; i < player.skills.size(); ++i) {
            const Skill& skill = player.skills[i];
            if (skill.unlocked && !skill.usedInBattle) {
                cout << "[" << (char)('1' + i) << "] Use skill: " << skill.name << endl;
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
    if (escaped) {
        cout << "You escaped from the fight!\n";
    } else if (player.hp <= 0) {
        cout << "You were defeated by the " << monster.name << "...\n";
    } else if (monster.hp <= 0) {
        cout << "You defeated the " << monster.name << "!\n";
        player.addExperience(monster.experience);
        cout << "You gained " << monster.experience << " experience!\n";
        player.addGold(monster.level * 5);
        cout << "You gained " << monster.level * 5 << " gold!\n";
    }

    if (isBossLevel && !bossAlreadyAttempted) {
        player.bossDefeatedLevel = player.level;
    }

    player.hp = player.maxHP;

    cout << "\nYour HP has been restored!\n";
    cout << "Press ESC to return to game menu..." << endl;
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
        cout << "Shop\n---------------------\n";
        cout << "Your gold: " << player.gold << endl;
        cout << "[B] Buy items\n";
        cout << "[S] Sell items\n";
        cout << "[ESC] Exit shop\n";
        char key = _getch();
        if (key == 27) break;

        if (key == 'b' || key == 'B') {
            while (true) {
                system("cls");
                cout << "Shop - Buy\n---------------------\n";
                cout << "Your gold: " << player.gold << endl;
                if (items.empty()) {
                    cout << "No items available to buy.\n";
                    cout << "[ESC] Back\n";
                    if (_getch() == 27) break;
                    continue;
                }
                for (size_t i = 0; i < items.size(); ++i) {
                    cout << "[" << i + 1 << "] " << items[i].name << " (Price: " << items[i].price << ")\n";
                }
                cout << "[ESC] Back\n";
                char buyKey = _getch();
                if (buyKey == 27) break;
                int idx = buyKey - '1';
                if (idx >= 0 && idx < items.size()) {
                    if (player.gold >= items[idx].price) {
                        player.gold -= items[idx].price;
                        player.addToBackpack(items[idx]);
                        cout << "You bought " << items[idx].name << "!\n";
                        items.erase(items.begin() + idx);
                    } else {
                        cout << "Not enough gold!\n";
                    }
                    cout << "Press any key...\n";
                    (void)_getch();
                }
            }
        } else if (key == 's' || key == 'S') {
            while (true) {
                system("cls");
                cout << "Shop - Sell\n---------------------\n";
                cout << "Your gold: " << player.gold << endl;

                vector<size_t> sellableIndices;
                for (size_t i = 0; i < player.backpack.size(); ++i) {
                    if (!player.backpack[i].equipped) {
                        sellableIndices.push_back(i);
                    }
                }

                if (sellableIndices.empty()) {
                    cout << "No unequipped items to sell in your backpack.\n";
                    cout << "[ESC] Back\n";
                    if (_getch() == 27) break;
                    continue;
                }

                for (size_t i = 0; i < sellableIndices.size(); ++i) {
                    size_t idx = sellableIndices[i];
                    cout << "[" << i + 1 << "] " << player.backpack[idx].name
                         << " (Sell price: " << player.backpack[idx].price / 2 << ")\n";
                }
                cout << "[ESC] Back\n";
                char sellKey = _getch();
                if (sellKey == 27) break;
                int choice = sellKey - '1';
                if (choice >= 0 && choice < sellableIndices.size()) {
                    size_t realIdx = sellableIndices[choice];
                    int sellPrice = player.backpack[realIdx].price / 2;
                    player.gold += sellPrice;
                    cout << "You sold " << player.backpack[realIdx].name << " for " << sellPrice << " gold!\n";
                    player.backpack.erase(player.backpack.begin() + realIdx);
                    cout << "Press any key...\n";
                    (void)_getch();
                }
            }
        }
    }
    system("cls");
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
void temple(Player& player) {
    system("cls");
    cout << "Temple\n---------------------\n";
    if (player.level < 10) {
        cout << "You need to be at least level 10 to choose a profession.\n";
        (void)_getch();
        system("cls");
        return;
    }
    if (player.profession == Profession::None) {
        cout << "Choose your profession:\n";
        cout << "[1] Warrior\n";
        cout << "[2] Archer\n";
        cout << "[3] Mage\n";
        char key = _getch();
        if (key == '1') player.profession = Profession::Warrior;
        else if (key == '2') player.profession = Profession::Archer;
        else if (key == '3') player.profession = Profession::Mage;
        else {
            cout << "Invalid choice.\nPress any key...\n";
            (void)_getch();
            system("cls");
            return;
        }
        player.skills = getSkillsForProfession(player.profession);
        cout << "You are now a ";
        switch (player.profession) {
        case Profession::Warrior: cout << "Warrior"; break;
        case Profession::Archer: cout << "Archer"; break;
        case Profession::Mage: cout << "Mage"; break;
        default: break;
        }
        cout << "!\nPress any key...\n";
        (void)_getch();
        system("cls");
        return;
    }

    cout << "Skill list:\n";
    for (size_t i = 0; i < player.skills.size(); ++i) {
        const Skill& skill = player.skills[i];
        cout << "[" << i + 1 << "] " << skill.name << " - " << skill.description
            << " (Required level: " << skill.requiredLevel << ") ";
        if (skill.unlocked) cout << "[UNLOCKED]";
        else if (player.level >= skill.requiredLevel) cout << "[AVAILABLE]";
        else cout << "[LOCKED]";
        cout << endl;
    }
    cout << "Select skill number to unlock or ESC to exit.\n";
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
            cout << "Skill unlocked: " << skill.name << "!\n";
        }
        else if (skill.unlocked) {
            cout << "Skill already unlocked.\n";
        }
        else {
            cout << "You need higher level for this skill.\n";
        }
        (void)_getch();
    }
    system("cls");
}

vector<Item> getShopItemsForLevel(int level) {
    vector<Item> items;
    if (level < 10) {
        items.push_back(Item("Wooden Sword", ItemType::Weapon, 10, 3, 0));
        items.push_back(Item("Cloth Helmet", ItemType::Helmet, 8, 0, 2));
        items.push_back(Item("Cloth Armor", ItemType::Armor, 12, 0, 4));
        items.push_back(Item("Cloth Pants", ItemType::Pants, 7, 0, 2));
        items.push_back(Item("Cloth Boots", ItemType::Boots, 5, 0, 2));
    } else if (level < 20) {
        items.push_back(Item("Bronze Sword", ItemType::Weapon, 25, 6, 0));
        items.push_back(Item("Bronze Helmet", ItemType::Helmet, 20, 0, 4));
        items.push_back(Item("Bronze Armor", ItemType::Armor, 30, 0, 8));
        items.push_back(Item("Bronze Pants", ItemType::Pants, 15, 0, 4));
        items.push_back(Item("Bronze Boots", ItemType::Boots, 12, 0, 3));
    } else if (level < 30) {
        items.push_back(Item("Iron Sword", ItemType::Weapon, 50, 10, 0));
        items.push_back(Item("Iron Helmet", ItemType::Helmet, 40, 0, 6));
        items.push_back(Item("Iron Armor", ItemType::Armor, 60, 0, 12));
        items.push_back(Item("Iron Pants", ItemType::Pants, 30, 0, 6));
        items.push_back(Item("Iron Boots", ItemType::Boots, 25, 0, 5));
    } else if (level < 40) {
        items.push_back(Item("Steel Sword", ItemType::Weapon, 90, 16, 0));
        items.push_back(Item("Steel Helmet", ItemType::Helmet, 70, 0, 9));
        items.push_back(Item("Steel Armor", ItemType::Armor, 120, 0, 18));
        items.push_back(Item("Steel Pants", ItemType::Pants, 55, 0, 8));
        items.push_back(Item("Steel Boots", ItemType::Boots, 40, 0, 7));
    } else if (level < 50) {
        items.push_back(Item("Silver Sword", ItemType::Weapon, 150, 22, 0));
        items.push_back(Item("Silver Helmet", ItemType::Helmet, 120, 0, 12));
        items.push_back(Item("Silver Armor", ItemType::Armor, 200, 0, 24));
        items.push_back(Item("Silver Pants", ItemType::Pants, 90, 0, 10));
        items.push_back(Item("Silver Boots", ItemType::Boots, 65, 0, 8));
    } else if (level < 60) {
        items.push_back(Item("Gold Sword", ItemType::Weapon, 220, 28, 0));
        items.push_back(Item("Gold Helmet", ItemType::Helmet, 180, 0, 15));
        items.push_back(Item("Gold Armor", ItemType::Armor, 300, 0, 32));
        items.push_back(Item("Gold Pants", ItemType::Pants, 130, 0, 12));
        items.push_back(Item("Gold Boots", ItemType::Boots, 90, 0, 10));
    } else if (level < 70) {
        items.push_back(Item("Crystal Sword", ItemType::Weapon, 300, 35, 0));
        items.push_back(Item("Crystal Helmet", ItemType::Helmet, 250, 0, 18));
        items.push_back(Item("Crystal Armor", ItemType::Armor, 400, 0, 40));
        items.push_back(Item("Crystal Pants", ItemType::Pants, 170, 0, 15));
        items.push_back(Item("Crystal Boots", ItemType::Boots, 120, 0, 12));
    } else if (level < 80) {
        items.push_back(Item("Obsidian Sword", ItemType::Weapon, 400, 42, 0));
        items.push_back(Item("Obsidian Helmet", ItemType::Helmet, 320, 0, 22));
        items.push_back(Item("Obsidian Armor", ItemType::Armor, 550, 0, 48));
        items.push_back(Item("Obsidian Pants", ItemType::Pants, 220, 0, 18));
        items.push_back(Item("Obsidian Boots", ItemType::Boots, 160, 0, 14));
    } else if (level < 90) {
        items.push_back(Item("Dragon Sword", ItemType::Weapon, 550, 50, 0));
        items.push_back(Item("Dragon Helmet", ItemType::Helmet, 420, 0, 26));
        items.push_back(Item("Dragon Armor", ItemType::Armor, 700, 0, 56));
        items.push_back(Item("Dragon Pants", ItemType::Pants, 300, 0, 20));
        items.push_back(Item("Dragon Boots", ItemType::Boots, 210, 0, 16));
    } else if (level < 100) {
        items.push_back(Item("Demonic Sword", ItemType::Weapon, 700, 60, 0));
        items.push_back(Item("Demonic Helmet", ItemType::Helmet, 550, 0, 30));
        items.push_back(Item("Demonic Armor", ItemType::Armor, 900, 0, 64));
        items.push_back(Item("Demonic Pants", ItemType::Pants, 380, 0, 24));
        items.push_back(Item("Demonic Boots", ItemType::Boots, 270, 0, 18));
    } else {
        items.push_back(Item("Legendary Sword", ItemType::Weapon, 1000, 80, 0));
        items.push_back(Item("Legendary Helmet", ItemType::Helmet, 800, 0, 40));
        items.push_back(Item("Legendary Armor", ItemType::Armor, 1500, 0, 90));
        items.push_back(Item("Legendary Pants", ItemType::Pants, 600, 0, 35));
        items.push_back(Item("Legendary Boots", ItemType::Boots, 400, 0, 25));
    }
    return items;
}

