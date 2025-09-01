#pragma once
#include <string>
using namespace std;

enum class ItemType { Weapon, Helmet, Armor, Pants, Boots };

class Item {
public:
    string name;
    ItemType type;
    int price;
    int attackBonus;
    int armorBonus;
    bool equipped;

    Item(const string& name, ItemType type, int price, int attackBonus, int armorBonus);
};