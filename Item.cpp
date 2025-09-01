#include "Item.h"

Item::Item(const string& name, ItemType type, int price, int attackBonus, int armorBonus)
    : name(name), type(type), price(price), attackBonus(attackBonus), armorBonus(armorBonus), equipped(false) {}
