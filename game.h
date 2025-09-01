#pragma once
#include <vector>
#include "Player.h"
#include "Item.h"
using namespace std;

void showCharacterInfo(Player& player);
void gameMenu(Player& player);
void begin();
void fight(Player& player);
void shop(Player& player);
vector<Item> getShopItemsForLevel(int level);