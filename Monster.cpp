#include <cstdlib>
#include <vector>
#include "Monster.h"
using namespace std;
Monster::Monster()
    : Character("", 1, 1, 1, 0), experience(0) {}

Monster::Monster(const string& name, int level, int maxHP, int attack, int armor, int experience)
    : Character(name, level, maxHP, attack, armor), experience(experience) {}

vector<Monster> Monster::getMonstersForLevel(int playerLevel) {
    vector<Monster> monsters;
    if (playerLevel < 5) {
        monsters = {
            Monster("Rat", 1, 12, 3, 0, 6),
            Monster("Bug", 2, 14, 4, 0, 7),
            Monster("Bat", 3, 16, 4, 1, 8),
            Monster("Mouse", 2, 13, 3, 0, 6),
            Monster("Worm", 1, 11, 2, 0, 5)
        };
    } else if (playerLevel < 10) {
        monsters = {
            Monster("Snake", 5, 22, 6, 1, 12),
            Monster("Spider", 7, 25, 7, 2, 14),
            Monster("Frog", 6, 20, 6, 1, 11),
            Monster("Centipede", 8, 27, 8, 2, 15),
            Monster("Scorpion", 9, 29, 9, 2, 17)
        };
    } else if (playerLevel < 15) {
        monsters = {
            Monster("Wolf", 10, 36, 10, 3, 20),
            Monster("Goblin", 12, 38, 11, 3, 22),
            Monster("Wild Dog", 11, 34, 9, 2, 18),
            Monster("Bandit", 13, 40, 12, 4, 24),
            Monster("Boar", 14, 42, 13, 4, 26),
            Monster("Fox", 12, 35, 10, 2, 19)
        };
    } else if (playerLevel < 20) {
        monsters = {
            Monster("Skeleton", 15, 48, 14, 5, 28),
            Monster("Zombie", 17, 52, 15, 5, 30),
            Monster("Ghoul", 18, 54, 16, 6, 32),
            Monster("Bandit Leader", 19, 56, 17, 6, 34),
            Monster("Wild Cat", 16, 46, 13, 4, 27)
        };
    } else if (playerLevel < 25) {
        monsters = {
            Monster("Orc", 20, 58, 18, 7, 37),
            Monster("Giant Bat", 22, 62, 19, 7, 40),
            Monster("Lizardman", 23, 64, 20, 8, 42),
            Monster("Troll", 24, 66, 21, 8, 44),
            Monster("Wild Boar", 21, 60, 17, 6, 35)
        };
    } else if (playerLevel < 30) {
        monsters = {
            Monster("Ogre", 25, 70, 22, 9, 48),
            Monster("Wasp", 27, 74, 23, 9, 51),
            Monster("Minotaur", 28, 76, 24, 10, 53),
            Monster("Harpy", 29, 78, 25, 10, 55),
            Monster("Wild Wolf", 26, 72, 21, 8, 46)
        };
    } else if (playerLevel < 35) {
        monsters = {
            Monster("Golem", 30, 82, 26, 12, 58),
            Monster("Ghoul Lord", 32, 86, 27, 12, 61),
            Monster("Vampire", 33, 88, 28, 13, 63),
            Monster("Werewolf", 34, 90, 29, 13, 65),
            Monster("Wild Bear", 31, 84, 25, 11, 56)
        };
    } else if (playerLevel < 40) {
        monsters = {
            Monster("Elemental", 35, 94, 30, 14, 68),
            Monster("Manticore", 37, 98, 31, 14, 71),
            Monster("Chimera", 38, 100, 32, 15, 73),
            Monster("Basilisk", 39, 102, 33, 15, 75),
            Monster("Wild Lion", 36, 96, 29, 13, 66)
        };
    } else if (playerLevel < 45) {
        monsters = {
            Monster("Hydra", 40, 106, 34, 16, 78),
            Monster("Wyvern", 42, 110, 35, 16, 81),
            Monster("Demon", 43, 112, 36, 17, 83),
            Monster("Dark Knight", 44, 114, 37, 17, 85),
            Monster("Wild Tiger", 41, 108, 31, 15, 76)
        };
    } else if (playerLevel < 50) {
        monsters = {
            Monster("Ancient Dragon", 45, 118, 38, 18, 88),
            Monster("Phoenix", 47, 122, 39, 18, 91),
            Monster("Archdemon", 48, 124, 40, 19, 93),
            Monster("Lich", 49, 126, 41, 19, 95),
            Monster("Wild Elephant", 46, 120, 35, 17, 86)
        };
    } else if (playerLevel < 55) {
        monsters = {
            Monster("Titan", 50, 130, 42, 20, 98),
            Monster("Behemoth", 52, 134, 43, 20, 101),
            Monster("Leviathan", 53, 136, 44, 21, 103),
            Monster("Seraph", 54, 138, 45, 21, 105),
            Monster("Wild Rhino", 51, 132, 39, 19, 96)
        };
    } else if (playerLevel < 60) {
        monsters = {
            Monster("Void Lord", 55, 142, 46, 22, 108),
            Monster("Celestial Guardian", 57, 146, 47, 22, 111),
            Monster("Dread Knight", 58, 148, 48, 23, 113),
            Monster("Storm Giant", 59, 150, 49, 23, 115),
            Monster("Wild Crocodile", 56, 144, 43, 21, 106)
        };
    } else if (playerLevel < 65) {
        monsters = {
            Monster("Frost Wyrm", 60, 154, 50, 24, 118),
            Monster("Fire Lord", 62, 158, 51, 24, 121),
            Monster("Thunder Beast", 63, 160, 52, 25, 123),
            Monster("Sand Serpent", 64, 162, 53, 25, 125),
            Monster("Wild Gorilla", 61, 156, 47, 23, 116)
        };
    } else if (playerLevel < 70) {
        monsters = {
            Monster("Nightmare", 65, 166, 54, 26, 128),
            Monster("Specter", 67, 170, 55, 26, 131),
            Monster("Wraith", 68, 172, 56, 27, 133),
            Monster("Banshee", 69, 174, 57, 27, 135),
            Monster("Wild Buffalo", 66, 168, 51, 25, 126)
        };
    } else if (playerLevel < 75) {
        monsters = {
            Monster("Hellhound", 70, 178, 58, 28, 138),
            Monster("Cerberus", 72, 182, 59, 28, 141),
            Monster("Griffin", 73, 184, 60, 29, 143),
            Monster("Pegasus", 74, 186, 61, 29, 145),
            Monster("Wild Moose", 71, 180, 55, 27, 136)
        };
    } else if (playerLevel < 80) {
        monsters = {
            Monster("Colossus", 75, 190, 62, 30, 148),
            Monster("Kraken", 77, 194, 63, 30, 151),
            Monster("Cyclops", 78, 196, 64, 31, 153),
            Monster("Medusa", 79, 198, 65, 31, 155),
            Monster("Wild Hippo", 76, 192, 59, 29, 146)
        };
    } else if (playerLevel < 85) {
        monsters = {
            Monster("Spectral Dragon", 80, 202, 66, 32, 158),
            Monster("Shadow Lord", 82, 206, 67, 32, 161),
            Monster("Death Knight", 83, 208, 68, 33, 163),
            Monster("Plague Bringer", 84, 210, 69, 33, 165),
            Monster("Wild Camel", 81, 204, 63, 31, 156)
        };
    } else if (playerLevel < 90) {
        monsters = {
            Monster("Elder Demon", 85, 214, 70, 34, 168),
            Monster("Archangel", 87, 218, 71, 34, 171),
            Monster("Dragon King", 88, 220, 72, 35, 173),
            Monster("Celestial Beast", 89, 222, 73, 35, 175),
            Monster("Wild Horse", 86, 216, 67, 33, 166)
        };
    } else if (playerLevel < 95) {
        monsters = {
            Monster("Abyssal Horror", 90, 226, 74, 36, 178),
            Monster("Star Serpent", 92, 230, 75, 36, 181),
            Monster("Cosmic Titan", 93, 232, 76, 37, 183),
            Monster("Solar Phoenix", 94, 234, 77, 37, 185),
            Monster("Wild Deer", 91, 228, 71, 35, 176)
        };
    } else if (playerLevel < 100) {
        monsters = {
            Monster("Demonic Emperor", 95, 238, 78, 38, 188),
            Monster("Heavenly Guardian", 97, 242, 79, 38, 191),
            Monster("Void Reaper", 98, 244, 80, 39, 193),
            Monster("Eternal Dragon", 99, 246, 81, 39, 195),
            Monster("Wild Elk", 96, 240, 75, 37, 186)
        };
    } else {
        monsters = {
            Monster("Apocalypse Dragon", 100, 300, 110, 55, 300),
            Monster("World Titan", 100, 290, 105, 53, 290),
            Monster("Celestial Phoenix", 100, 280, 100, 51, 280),
            Monster("Eternal Seraph", 100, 270, 95, 49, 270),
            Monster("Final Behemoth", 100, 260, 90, 47, 260),
            Monster("Legendary Hydra", 100, 250, 85, 45, 250),
            Monster("Mythic Leviathan", 100, 240, 80, 43, 240),
            Monster("Ultimate Demon", 100, 230, 75, 41, 230),
            Monster("Supreme Lich", 100, 220, 70, 39, 220),
            Monster("Immortal Golem", 100, 210, 65, 37, 210)
        };
    }
    return monsters;
}

Monster Monster::getRandomMonster(int playerLevel) {
    vector<Monster> monsters = getMonstersForLevel(playerLevel);
    int r = rand() % monsters.size();
    return monsters[r];
}

static const vector<Monster> bosses = {
    Monster("Skeleton King", 5, 140, 14, 7, 70),
    Monster("Lich Queen", 10, 245, 24, 14, 140),
    Monster("Dragon Lord", 15, 350, 35, 20, 200),
    Monster("Demon Overlord", 20, 560, 49, 28, 320),
    Monster("Frost Giant", 25, 840, 63, 36, 480),
    Monster("Vampire Prince", 30, 1120, 77, 44, 640),
    Monster("Hydra", 35, 1400, 91, 52, 800),
    Monster("Phoenix", 40, 1680, 105, 60, 960),
    Monster("Ancient Golem", 45, 1960, 119, 68, 1120),
    Monster("Shadow Emperor", 50, 2240, 133, 76, 1280),
    Monster("Celestial Seraph", 55, 2520, 147, 84, 1440),
    Monster("Abyssal Leviathan", 60, 2800, 161, 92, 1600),
    Monster("Storm Titan", 65, 3080, 175, 100, 1760),
    Monster("Eternal Warden", 70, 3360, 189, 108, 1920),
    Monster("Cosmic Reaper", 75, 3640, 203, 116, 2080),
    Monster("Time Lich", 80, 3920, 217, 124, 2240),
    Monster("Void Dragon", 85, 4200, 231, 132, 2400),
    Monster("Dread Overlord", 90, 4480, 245, 140, 2560),
    Monster("Divine Judge", 95, 4760, 259, 148, 2720),
    Monster("Legendary Calvaria", 100, 5040, 273, 156, 2880)
};

Monster Monster::getBossForLevel(int level) {
    for (const auto& boss : bosses) {
        if (boss.level == level) return boss;
    }
}