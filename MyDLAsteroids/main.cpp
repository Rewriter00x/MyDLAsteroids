#include <iostream>
#include "MyDLAsteroidsFramework.h"
#include "MyFramework.h"

static int ScreenWidth = 1024;
static int ScreenHeight = 768;
static int MapWidth = ScreenWidth * 2;
static int MapHeight = ScreenHeight * 2;
static int EnemyNumber = 100;
static int Ammo = 3;
static float AbilityChance = 0.2;

static const int MaxEnemyNumber = 200;
static const float MaxAbilityChance = 1.0f;

enum class Vars {
    WINDOW = 0,
    MAP,
    NUM_ASTEROIDS,
    NUM_AMMO,
    ABILITY_PROBABILITY,
};

static const int varc = 5;
static const char* varv[varc]
    {"-window", "-map", "-num_asteroids", "-num_ammo", "-ability_probability"};

void parseInt(char* value, int& res) {
    int i = atoi(value);
    if (i == 0) {
        std::cerr << "Bad value " << value << std::endl;
        return;
    }
    res = i;
}

void parseFloat(char* value, float& res) {
    float f = atof(value);
    if (f == 0.0f) {
        std::cerr << "Bad value " << value << std::endl;
        return;
    }
    res = f;
}

void parseSize(char* value, int& width, int& height) {
    char v[strlen(value)];
    for (int i = 0; i < strlen(value); i++)
        v[i] = value[i];
    const char* w = strtok(v, "x");
    const char* h = strtok(nullptr, "x");
    int i = atoi(w);
    int j = atoi(h);
    if (i == 0 || j == 0) {
        std::cerr << "Bad value " << value << std::endl;
        return;
    }
    width = i;
    height = j;
}

void parse(Vars i, char* value) {
    switch(i) {
        case Vars::WINDOW:
            parseSize(value, ScreenWidth, ScreenHeight);
            break;
        case Vars::MAP:
            parseSize(value, MapWidth, MapHeight);
            break;
        case Vars::NUM_ASTEROIDS:
            int num;
            parseInt(value, num);
            if (num > MaxEnemyNumber) {
                std::cerr << "Bad value " << value << std::endl;
                return;
            }
            EnemyNumber = num;
            break;
        case Vars::NUM_AMMO:
            parseInt(value, Ammo);
            break;
        case Vars::ABILITY_PROBABILITY:
            float chance;
            parseFloat(value, chance);
            if (chance > MaxAbilityChance) {
                std::cerr << "Bad value " << value << std::endl;
                return;
            }
            AbilityChance = chance;
            break;
    }
}

void parse(const char* variable, char* value) {
    int i = 0;
    for (; i < varc; i++)
        if (variable == varv[i]) {
            parse(Vars(i), value);
            return;
        }
    std::cerr << "Bad variable " << variable << std::endl;
}

int main(int argc, char* argv[]) {
    srand((unsigned int)time(0));
    for (int i = 1; i < argc; i += 2) {
        if (i + 1 >= argc) {
            std::cerr << "Missing value for argument " << argv[i] << std::endl;
            break;
        }
        parse(argv[i], argv[i + 1]);
    }
    
    std::cout << "window: " << ScreenWidth << "x" << ScreenHeight << "\n";
    std::cout << "map: " << MapWidth << "x" << MapHeight << "\n";
    std::cout << "num_asteroids: " << EnemyNumber << "\n";
    std::cout << "num_ammo: " << Ammo << "\n";
    std::cout << "ability_probability: " << AbilityChance << "\n";
    
    return run(new MyDLAsteroidsFramework(ScreenWidth, ScreenHeight, MapWidth, MapHeight, EnemyNumber, Ammo, AbilityChance));
    //return run(new MyFramework);
}
